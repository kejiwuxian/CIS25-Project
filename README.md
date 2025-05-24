# CIS25 Project

This repository contains the source code for CIS25 Project.

### Please stay tuned for a serverless website version of this program written in JavaScript.

Unit Price Calculator.  
A program that calculates a product's unit price in another weight unit and currency.  
It also allows user to build sorted catalogs of different products from multiple sources by entering their price tag in different currencies and units.  
It fetches the current currency conversion rate from an API[^1] and calculates the unit price in the target weight unit and target currency.

## [Project Presentation](https://youtu.be/tFs2VjBvsQM)

## How to compile
```
cd build
cmake ..
cmake --build .
```

## How to run
```
cd build/Debug
main_exec
```

## How to run Google Test
```
cd build/Debug
test_exec
```

[^1]: Free Currency Exchange Rates API [exchange-api](https://github.com/fawazahmed0/exchange-api).