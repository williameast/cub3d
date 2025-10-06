#!/usr/bin/env python3

import os
import subprocess
import sys
import time
from pathlib import Path

# Colors for output
GREEN = '\033[92m'
RED = '\033[91m'
YELLOW = '\033[93m'
BLUE = '\033[94m'
CYAN = '\033[96m'
RESET = '\033[0m'

def run_test(cub3d_path, map_path, timeout=5):
    """Run cub3d without valgrind for quick testing"""
    cmd = [cub3d_path, map_path]

    try:
        start_time = time.time()
        result = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=timeout,
            text=True
        )
        elapsed = time.time() - start_time
        return result, elapsed
    except subprocess.TimeoutExpired:
        return None, None

def run_valgrind_test(cub3d_path, map_path):
    """Run cub3d with valgrind (no timeout)"""
    cmd = [
        'valgrind',
        '--suppressions=valgrind.supp',
        '--leak-check=full',
        '--show-leak-kinds=all',
        '--errors-for-leak-kinds=all',
        '--error-exitcode=42',
        '--quiet',
        cub3d_path,
        map_path
    ]

    try:
        result = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        return result
    except Exception as e:
        return None

def main():
    # Paths
    cub3d_path = './build/cub3d'
    maps_dir = Path('build/maps/testing')

    # Check if cub3d exists
    if not os.path.exists(cub3d_path):
        print(f"{RED}Error: cub3d executable not found at {cub3d_path}{RESET}")
        sys.exit(1)

    # Check if valgrind is available
    try:
        subprocess.run(['valgrind', '--version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except FileNotFoundError:
        print(f"{RED}Error: valgrind not found. Please install valgrind.{RESET}")
        sys.exit(1)

    # Collect test cases
    valid_maps = sorted(maps_dir.glob('valid/*.cub')) if (maps_dir / 'valid').exists() else []
    invalid_maps = sorted(maps_dir.glob('invalid/*.cub')) if (maps_dir / 'invalid').exists() else []

    if not valid_maps and not invalid_maps:
        print(f"{YELLOW}No test maps found in {maps_dir}{RESET}")
        sys.exit(0)

    passed = 0
    failed = 0
    total_time = 0

    print(f"{BLUE}{'='*70}{RESET}")
    print(f"{BLUE}Running cub3d tests{RESET}")
    print(f"{BLUE}{'='*70}{RESET}\n")

    # Test valid maps
    if valid_maps:
        print(f"{BLUE}Testing VALID maps (should pass):{RESET}\n")
        for map_path in valid_maps:
            map_name = map_path.name

            # Step 1: Quick test without valgrind
            result, elapsed = run_test(cub3d_path, str(map_path))

            if result is None:
                print(f"  {RED}✗ FAIL{RESET} {map_name}: Timeout (>5s)")
                print(f"         Program took too long to execute\n")
                failed += 1
                continue

            if result.returncode != 0:
                print(f"  {RED}✗ FAIL{RESET} {map_name}: Exit code {result.returncode} ({elapsed:.3f}s)")
                if result.stdout:
                    print(f"         stdout: {result.stdout[:200]}")
                if result.stderr:
                    print(f"         stderr: {result.stderr[:200]}")
                print()
                failed += 1
                continue

            # Step 2: Check for leaks with valgrind
            print(f"  {CYAN}Testing{RESET} {map_name} ({elapsed:.3f}s) - checking leaks...", end='', flush=True)
            valgrind_result = run_valgrind_test(cub3d_path, str(map_path))

            if valgrind_result is None:
                print(f"\r  {RED}✗ FAIL{RESET} {map_name}: Valgrind error")
                failed += 1
                continue

            if valgrind_result.returncode == 0:
                print(f"\r  {GREEN}✓ PASS{RESET} {map_name} ({elapsed:.3f}s)")
                passed += 1
                total_time += elapsed
            else:
                print(f"\r  {RED}✗ FAIL{RESET} {map_name}: Memory leaks detected ({elapsed:.3f}s)")
                if valgrind_result.stderr:
                    print(f"         {valgrind_result.stderr[:500]}")
                print()
                failed += 1

    # Test invalid maps
    if invalid_maps:
        print(f"\n{BLUE}Testing INVALID maps (should fail gracefully):{RESET}\n")
        for map_path in invalid_maps:
            map_name = map_path.name

            # Step 1: Quick test without valgrind
            result, elapsed = run_test(cub3d_path, str(map_path))

            if result is None:
                print(f"  {RED}✗ FAIL{RESET} {map_name}: Timeout (>5s)")
                print(f"         Program took too long to execute\n")
                failed += 1
                continue

            if result.returncode == 0:
                print(f"  {RED}✗ FAIL{RESET} {map_name}: Exit code 0 ({elapsed:.3f}s)")
                print(f"         Invalid map was accepted (should have been rejected)\n")
                failed += 1
                continue

            # Step 2: Check for leaks with valgrind
            print(f"  {CYAN}Testing{RESET} {map_name} ({elapsed:.3f}s) - checking leaks...", end='', flush=True)
            valgrind_result = run_valgrind_test(cub3d_path, str(map_path))

            if valgrind_result is None:
                print(f"\r  {RED}✗ FAIL{RESET} {map_name}: Valgrind error")
                failed += 1
                continue

            # Invalid maps should exit non-zero BUT with no valgrind errors (exit 42)
            if valgrind_result.returncode != 0 and valgrind_result.returncode != 42:
                print(f"\r  {GREEN}✓ PASS{RESET} {map_name} ({elapsed:.3f}s, rejected correctly)")
                passed += 1
                total_time += elapsed
            else:
                print(f"\r  {RED}✗ FAIL{RESET} {map_name}: Memory leaks detected ({elapsed:.3f}s)")
                if valgrind_result.stderr:
                    print(f"         {valgrind_result.stderr[:500]}")
                print()
                failed += 1

    # Summary
    total = passed + failed
    print(f"\n{BLUE}{'='*70}{RESET}")
    print(f"{BLUE}Summary:{RESET}")
    print(f"  Total tests: {total}")
    print(f"  {GREEN}Passed: {passed}{RESET}")
    print(f"  {RED}Failed: {failed}{RESET}")
    if passed > 0:
        print(f"  {CYAN}Total execution time: {total_time:.3f}s{RESET}")
        print(f"  {CYAN}Average time per passing test: {total_time/passed:.3f}s{RESET}")
    print(f"{BLUE}{'='*70}{RESET}")

    sys.exit(0 if failed == 0 else 1)

if __name__ == '__main__':
    main()
