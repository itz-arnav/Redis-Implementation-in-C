# Coding a FAST Redis database server in C

This project demonstrates a simple Redis database server implementation on Windows, accepting connections and sending a message to connected clients. This is based on Dr. Jonas Birch's video tutorial.

## Requirements

- **Telnet**: Ensure Telnet is enabled on your Windows system.
- **MinGW Compiler**: Install MinGW to compile the project.
- **Make**: Install Make to manage the build process.

## Enabling Telnet on Windows

1. Open Control Panel.
2. Go to Programs and Features.
3. Click on "Turn Windows features on or off".
4. Scroll down and check "Telnet Client".
5. Click OK and wait for the installation to complete.

## Setting Up MinGW

1. Download and install MinGW from [MinGW SourceForge](http://www.mingw.org/).
2. During installation, ensure you select `mingw32-base` and `mingw32-gcc-g++` components.
3. Add the path to MinGW `bin` directory to your system's PATH environment variable. This directory typically looks like `C:\MinGW\bin`.

## Installing Make

1. Download `make` from the [GNUWin32 project](http://gnuwin32.sourceforge.net/packages/make.htm).
2. Extract the contents and add the path to the `bin` directory to your system's PATH environment variable.

## Building and Running the Server

1. Clone the repository:

   ```sh
   git clone <repository-url>
   cd <repository-directory>
   ```

2. Build the project:

   ```sh
   make
   ```

3. Run the server:

   ```sh
   ./server.exe
   ```

4. Open a command prompt and connect to the server using Telnet:
   ```sh
   telnet 127.0.0.1 1567
   ```

You should see the message "200 Connected to Cache server".

## Thanks

Special thanks to Dr. Jonas Birch for his video tutorial on this project. This repository is the Windows version of that tutorial.

You can watch the original tutorial [here](https://www.youtube.com/watch?v=FFxEoQyNQKM).
