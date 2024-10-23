{ pkgs ? import <nixos> {} , ... } : 
pkgs.mkShell {
    packages = with pkgs; [
      clang-tools
      clang
      bear
      gnumake
      pkg-config
      valgrind
      libGL
      glfw
    ];
}
