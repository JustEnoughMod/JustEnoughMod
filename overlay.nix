{ dylib, ... }:
final: _: {
  JustEnoughMod = with final;
    clangStdenv.mkDerivation {
      name = "JustEnoughMod";

      src = ./.;

      enableParallelBuilding = true;

      nativeBuildInputs =
        [ clang-tools pkg-config meson ninja makeWrapper doxygen graphviz ];
      buildInputs = [ SDL2 spdlog vulkan-loader wayland ];

      preConfigure = ''
        cp -r ${dylib} subprojects/dylib

        chmod 777 -R subprojects
      '';

      installPhase = ''
        mkdir -p $out/bin
        mkdir -p $out/bin/Plugins
        cp JustEnoughMod $out/bin
        cp libJustEnoughMod.so $out/bin
        wrapProgram $out/bin/JustEnoughMod \
          --prefix LD_LIBRARY_PATH : ${lib.makeLibraryPath [ vulkan-loader ]}
      '';
    };
}
