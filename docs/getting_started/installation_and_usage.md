
Astrea uses a small Python script to build out some files. In order to run this, first install the Astrea's python environment with
```bash
make python_env
```

Once this is built, activate the environment with
```bash
source ./.venv/bin/activate
```

Once the python is activated, build and install with
```bash
make install
```

Options can be added at either step to update the configuration accordingly.
```bash
make debug install
```
```bash
make relwithdebinfo tests examples build
make relwithdebinfo all install
```
where `all` can replace `tests examples`.

The build step only needs to be done once per independent bulid configuration.

There are also some simple commands to run all the tests and examples.
```bash
make run_tests
make run_examples
```

On build, files should be installed locally in the `install` folder. This process is fully customizable with standard cmake commands if you want a different build process, install location, etc. See the recipes in the Makefile for more details.