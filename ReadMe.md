# BASE64

A BASE64 encoder/decode library and executable.

## BUILDING
BASE64 uses CMake as its build system.

```bash
$ git clone https://github.com/devbumbuna/BASE64
$ cd BASE64
$ cmake -B build
$ cmake --build build
```
## INSTALLING
while inside the project repository run the following command(s).
```bash
$ cmake --install build
```
> **NOTE**: You may need to run the above command with admin privileges.

## USAGE

- executable
```bash
$ base64ed [option] [file] ...
[options]
    -d  decode files
    -v  version info
    -h  help
```

- library
```c
include <base64.h>

/**
 * @param inputFunctionPtr - pointer to a function with the signature
 *                           (unsigned char *buffer, int *bufferSize)
 * @param outputFunctionPtr - pointer to a function with the signature
 *                            (unsigned char *buffer, int *bufferSize)
 *
 */
if(base64Encode(inputFunctionPtr, outputFunctionPtr) != 0) {
    //report error
}

if(base64Decode(inputFunctionPtr, outputFunctionPtr) != 0) {
    //report error
}
```

## CONTRIBUTION
All contributions are welcomed. Make changes you deem necessary and i will review and merge them.
