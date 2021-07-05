This code was written for the group of Dr. Dan Higgins at Kansas State University to analyze some data they collected.

# Installing

There are two ways to install the executable: installing a prebuilt binary or building from source.

## Prebuilt Binary

Download the file corresponding to your system using one of the following links. If there isn't one for your system either build from source, or let me know and I can likely build a binary for you.

If on MacOS or Linux, you'll need to run the following command to make the binary executable:

```
chmod +x <file name>
```

| Operating System | Link                                                                                                    |
| ---------------- | ------------------------------------------------------------------------------------------------------- |
| Windows          | https://github.com/ehiggins98/AutoCorrelate-Photon-Data/releases/download/1.0.0/TimestampAC-windows.exe |
| MacOS            | https://github.com/ehiggins98/AutoCorrelate-Photon-Data/releases/download/1.0.0/TimestampAC-macos       |
| Ubuntu 18.04     | https://github.com/ehiggins98/AutoCorrelate-Photon-Data/releases/download/1.0.0/TimestampAC-ubuntu18.04 |
| Ubuntu 20.04     | https://github.com/ehiggins98/AutoCorrelate-Photon-Data/releases/download/1.0.0/TimestampAC-ubuntu20.04 |

## Building from Source

### Linux/MacOS

First, download the source code from this repository. If you have git installed then you can do this with the following command:

```
git clone https://github.com/ehiggins89/AutoCorrelate-Photon-Data
```

Otherwise, [download the code as a zip file](https://github.com/ehiggins98/AutoCorrelate-Photon-Data/archive/refs/heads/master.zip) and unzip it in your preferred location.

Then, simply run `make linux` for Linux, or `make macos` for MacOS. This will create a binary called "TimestampAC."

Optionally, you can also move the executable to a location on the system path, so it can be executed regardless of the terminal's current working directory. On MacOS, this can be done with the following command

```
mv TimestampAC-macos /usr/local/bin
```

with the command on Linux being analogous, with the corresponding binary name being used instead of the MacOS binary.

### Windows

These instructions are untested: let me know if you run into any problems.

First, install a the Visual C++ compiler [here](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019) (download the "Build Tools for Visual Studio 2019). Run the installer, and select the "C++ build tools" workflow to run. This should create several configurations in your Start menu - you'll want to use the "x64 Native Tools Command Prompt."

Now, download the source code from this repository. If you have git installed then you can do this with the following command:

```
git clone https://github.com/ehiggins89/AutoCorrelate-Photon-Data
```

Otherwise, [download the code as a zip file](https://github.com/ehiggins98/AutoCorrelate-Photon-Data/archive/refs/heads/master.zip) and unzip it in your preferred location.

Then, run `nmake windows`. This will create a binary called "TimestampAC.exe."

Optionally, you can also move the executable to a location on the system path, so it can be executed regardless of the command line's current working directory. To do this, follow [this guide](https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/#:~:text=Click%20the%20%E2%80%9CEnvironment%20Variables%E2%80%A6%E2%80%9D,path%20you%20want%20to%20add.) to add the directory containing your executable to the system path.

# Running the Code

Regardless of platform, the executable file takes several command line arguments:

| Flag, Short Form            | Required | Default Value | Example                                     | Description                                              |
| --------------------------- | -------- | ------------- | ------------------------------------------- | -------------------------------------------------------- |
| `--input-file-name`, `-if`  | Yes      | None          | `--input-file-name NR_20_KI_25M_60uW-0.stp` | The name of the file containing the input data.          |
| `--output-file-name`, `-of` | Yes      | None          | `--output-file-name output.csv`             | The name of the file where output data should be written |
| `--alpha`, `-a`             | No       | 5             | `--alpha 5`                                 | Number of bins by which to shift                         |
| `--start-log-time`, `-s`    | No       | -6.5          | `--start-log-time -6.5`                     | The base-10 log of the first bin size                    |
| `--inc-log-time`, `-i`      | No       | 0.1           | `--inc-log-time 0.1`                        | The base-10 log of the bin size increment                |
| `--end-log-time`, `-e`      | No       | 1             | `--end-log-time 1`                          | The base-10 log of the last bin size                     |

For example, on MacOS one might run the executable like this

```
./TimestampAC-macos -if NR_20_KI_25M_60uW-0.stp -of output.csv
```

or on Windows,

```
TimestampAC-windows.exe -if NR_20_KI_25M_60uW-0.stp -of output.csv
```
