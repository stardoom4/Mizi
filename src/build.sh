#!/bin/bash

rm ../site/*
rm main

make

./main -a
