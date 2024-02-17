{
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      lastModifiedDate =
        self.lastModifiedDate or self.lastModified or "19700101";
      version = builtins.substring 0 8 lastModifiedDate;

      supportedSystems =
        [ "x86_64-linux" "aarch64-linux" ];

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
            dylib = prev.fetchgit {
              url = "https://github.com/martin-olivier/dylib";
              rev = "d848a2fe1b0959443d1fcd7288dc4bc779e1f836";
              sha256 = "sha256-Pax8KYypbGVIReQuiwZ2kdgQqFuFYuoLA6YZgQLVE4w=";
              fetchSubmodules = true;
            };
          in stdenv.mkDerivation rec {
            pname = "JustEnoughMod";
            inherit version;

            src = ./.;

            enableParallelBuilding = true;

            nativeBuildInputs = [ pkg-config meson ninja ccache git binutils mold ];
            buildInputs = [
              alsa-lib
              audiofile
              dbus
              cmake
              egl-wayland
              glslang
              ibus
              jack2
              libGL
              libdecor
              libdrm
              libiconv
              libpulseaudio
              libunwind
              libusb1
              libxkbcommon
              mesa
              pcre2
              pipewire
              SDL2
              shaderc
              sndio
              udev
              util-linux
              vulkan-headers
              vulkan-loader
              vulkan-tools
              vulkan-validation-layers
              wayland
              wayland-protocols
              wayland-scanner
              xorg.libICE
              xorg.libX11
              xorg.libXScrnSaver
              xorg.libXcursor
              xorg.libXext
              xorg.libXi
              xorg.libXinerama
              xorg.libXrandr
              xorg.libXxf86vm
            ];

            VULKAN_SDK =
              "${vulkan-validation-layers}/share/vulkan/explicit_layer.d";

            preConfigure = ''
              cp -r ${bgfx} subprojects/bgfx
              cp -r ${dylib} subprojects/dylib

              chmod 777 -R subprojects
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
