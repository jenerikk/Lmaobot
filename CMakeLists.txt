name: Build Lmaobot Mod

on:
  push:
    branches: [ main ]
  workflow_dispatch:

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout repository
      uses: actions/checkout@v3

    - name: Install Rust
      uses: actions-rs/toolchain@v1
      with:
        toolchain: stable
        profile: minimal
        override: true

    - name: Install Geode CLI
      run: cargo install --git https://github.com/geode-sdk/cli --tag v3.7.0 --locked

    - name: Add Cargo bin to PATH
      run: echo "$HOME/.cargo/bin" >> $GITHUB_PATH

    - name: Build mod
      run: geode build
      working-directory: ${{ github.workspace }}

    - name: Upload .geode file
      uses: actions/upload-artifact@v4
      with:
        name: lmaobot
        path: build/*.geode
