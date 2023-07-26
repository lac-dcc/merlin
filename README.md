# 🧙‍♂️ Merlin 🧙‍♂️

<p align="center">
  <img alt="merlin drawing" src="assets/img/merlin.jpg" width="30%" height="auto"/></br>
</p>

## Introduction
Merlin is a tool that tries to infer the computational cost of C/C++ programs using polynomial interpolation. Merlin consists of two parts: a
`clang` plugin that adds instrumentation to programs by inserting counters, and a polynomial interpolator that uses the information generated by instrumentation to find a curve relating program inputs with computational cost. The figure below gives an overview of how Merlin works.
<p align="center">
  <img alt="merlin overview" src="assets/img/MerlinOverview.png" width="65%" height="auto"/></br>
</p>

## Instrumentation
Merlin's instrumentation was implemented as a `clang` plugin that inserts counters inside loops bodies to count the number of iterations required by a program. The resulting program after instrumentation generate output in `stdout` that is used by Merlin's interpolator to find a curve that describes the computational cost of that program.

## Interpolation
Merlin, when dealing with programs influenced by a single input variable, uses [Newton's Divided Differences](https://en.wikipedia.org/wiki/Newton_polynomial) method for interpolating data points to find polynomials that fit the given data exactly. However, when dealing with programs costs that are influenced by multiple variables, Merlin uses the [least squares method](https://en.wikipedia.org/wiki/Linear_least_squares) to find good approximations for the function costs of the programs.