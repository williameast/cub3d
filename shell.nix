{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    # Build tools
    cmake
    gnumake
    gcc
    pkg-config

    # Graphics libraries
    glfw
    libGL
    xorg.libX11
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXi
    xorg.libXext
  ];

  # Prevent mixing system and Nix headers
  NIX_ENFORCE_PURITY = 1;

  # Disable fortify source to allow -O0 debug builds
  hardeningDisable = [ "fortify" ];

  shellHook = ''
    # Clear system include paths to avoid header conflicts
    unset C_INCLUDE_PATH
    unset CPLUS_INCLUDE_PATH

    # Preserve display for GUI applications
    export DISPLAY=''${DISPLAY:-:0}

    echo "cub3d development environment loaded"
    echo "Run: cmake -B build && cmake --build build"
  '';
}
