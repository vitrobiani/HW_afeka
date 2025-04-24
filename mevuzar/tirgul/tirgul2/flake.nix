{
  description = "My Project with Declarative Commands";

  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        {
          devShells.default = pkgs.mkShell {
            buildInputs = [];
            shellHook = ''
                #!/bin/bash
                suffix=".c"
                echo "number of processes:  "
                read proc

                # Find the most recently edited .c file in the current directory
                recent_file=$(ls -t *$suffix 2>/dev/null | head -n 1)

                if [ -z "$recent_file" ]; then
                    echo "No $suffix files found in the current directory."
                else
                    echo "Most recently edited $suffix file: $recent_file"
                    
                    # Compile the file using gcc
                    mpicc "$recent_file" 
                    if [ $? -eq 0 ]; then
                        echo "Compilation successful. Executable 'output' created."
                    else
                        echo "Compilation failed."
                    fi
                fi
                mpiexec -np $proc ./a.out
                exit
            '';
          };
        }
      );
}
