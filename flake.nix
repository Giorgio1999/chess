{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
        in 
        with pkgs;
        {
          devShells.default = mkShell {
            nativeBuildInputs = with pkgs; [
              cmake
              gcc
            ];
            buildInputs = with pkgs; [
              gtest
            ];

            CXX_INCLUDE_PATH = "${pkgs.gcc-unwrapped}/include/c++/13.3.0/";
            CXX_LIBRARY_PATH = "${pkgs.gcc-unwrapped}/lib/gcc/13.3.0/";
            INSTALL_PREFIX = "/home/gio/.local";
            CMAKE_PREFIX_PATH="/run/current-system/sw";

            shellHook = ''
              echo "C++ Development Shell"
              echo "  with: $(g++ --version)"
              echo "  with: $(make --version)"
              export PATH=$PATH:$INSTALL_PREFIX/bin
              exec zsh
            '';
          };
        }
      );
}
