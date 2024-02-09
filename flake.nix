{
  description = "An over-engineered Hello World in C";

  outputs = { self, nixpkgs }:
    let
      lastModifiedDate =
        self.lastModifiedDate or self.lastModified or "19700101";
      version = builtins.substring 0 8 lastModifiedDate;

      supportedSystems =
        [ "x86_64-linux" "x86_64-darwin" "aarch64-linux" "aarch64-darwin" ];

      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;

      nixpkgsFor = forAllSystems (system:
        import nixpkgs {
          inherit system;
          overlays = [ self.overlay ];
        });
    in {
      overlay = final: prev: {

        JustEnoughMod = with final;
          let
            bgfx = prev.fetchgit {
              url = "https://github.com/bkaradzic/bgfx.cmake";
              rev = "011e8efe231d3d9aba9caf634dbc86d85263d20e";
              sha256 = "sha256-whNLa8ZCgfLXwnXnp4EczNWfMqvlO71eQnagpmW7p+c=";
              fetchSubmodules = true;
            };
            sdl = prev.fetchgit {
              url = "https://github.com/libsdl-org/SDL";
              rev = "859844eae358447be8d66e6da59b6fb3df0ed778";
              sha256 = "sha256-uKL9/T6vCEqMqmD3Q3rCMtKPRJZ4fRYVUr+4628/Ajg=";
              fetchSubmodules = true;
            };
          in clangStdenv.mkDerivation rec {
            pname = "JustEnoughMod";
            inherit version;

            src = ./.;

            enableParallelBuilding = true;

            nativeBuildInputs = [ pkg-config cmake ninja git binutils mold];
            buildInputs = [ xorg.libX11 xorg.libXScrnSaver xorg.libXinerama xorg.libXxf86vm xorg.libXi xorg.libICE xorg.libXrandr xorg.libXext xorg.libXcursor libGL alsa-lib audiofile dbus libdecor pipewire libpulseaudio udev
            wayland libxkbcommon libdrm mesa ibus libiconv wayland-protocols libunwind libusb1 jack2 sndio ];

            preConfigure = ''
              cp -r ${bgfx} vendor/bgfx
              cp -r ${sdl} vendor/sdl

              chmod 777 -R vendor
            '';

            installPhase = ''
              mkdir -p $out/bin
              mv ${pname} $out/bin
            '';
          };

      };

      packages = forAllSystems
        (system: { inherit (nixpkgsFor.${system}) JustEnoughMod; });

      defaultPackage =
        forAllSystems (system: self.packages.${system}.JustEnoughMod);

      nixosModules.JustEnoughMod = { pkgs, ... }: {
        nixpkgs.overlays = [ self.overlay ];

        environment.systemPackages = [ pkgs.JustEnoughMod ];
      };
    };
}
