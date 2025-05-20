# CIS25 Project

This repository contains the source code for CIS25 Project.

Unit Price Calculator.  
A program that calculates a product's unit price in another weight unit and currency.  
It prompts users to enter the product's net weight, weight unit, price, currency, target weight unit, and target currency.  
It then fetches the current currency conversion rate from an API[^1] and calculates the unit price in the target weight unit and target currency.

## [Project Presentation](https://youtu.be/TYXPYbKedRk)
## [Code walk through](https://youtu.be/yvOAlP9YSDo)

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