//                                               -*- C++ -*-
/**
 *  @brief OptimizationProblem implements an algorithm for finding the
 *
 *  Copyright 2005-2017 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "openturns/OptimizationProblem.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(OptimizationProblem);

/* Default constructor */
OptimizationProblem::OptimizationProblem() :
  TypedInterfaceObject<OptimizationProblemImplementation>(new OptimizationProblemImplementation())
{
  // Nothing to do
}

/* Constructor from an implementation */
OptimizationProblem::OptimizationProblem(const OptimizationProblemImplementation & implementation) :
  TypedInterfaceObject<OptimizationProblemImplementation>(implementation.clone())
{
  // Nothing to do
}

/* Constructor from a Pointer to an implementation */
OptimizationProblem::OptimizationProblem(const Implementation & p_implementation) :
  TypedInterfaceObject<OptimizationProblemImplementation>(p_implementation)
{
  // Nothing to do
}

/* Constructor with constraints, bounds */
OptimizationProblem::OptimizationProblem(const NumericalMathFunction & objective)
: TypedInterfaceObject<OptimizationProblemImplementation>(new OptimizationProblemImplementation(objective))
{
  // Nothing to do
}

/* Constructor with constraints, bounds */
OptimizationProblem::OptimizationProblem(const NumericalMathFunction & objective,
    const NumericalMathFunction & equalityConstraint,
    const NumericalMathFunction & inequalityConstraint,
    const Interval & bounds):
  TypedInterfaceObject<OptimizationProblemImplementation>(new OptimizationProblemImplementation(objective, equalityConstraint, inequalityConstraint, bounds))
{
  // Nothing to do
}

/* Constructor for nearest point problem */
OptimizationProblem::OptimizationProblem(const NumericalMathFunction & levelFunction,
    NumericalScalar levelValue)
  : TypedInterfaceObject<OptimizationProblemImplementation>(new OptimizationProblemImplementation(levelFunction, levelValue))
{
  // Nothing to do
}

/* Objective accessor */
NumericalMathFunction OptimizationProblem::getObjective() const
{
  return getImplementation()->getObjective();
}

void OptimizationProblem::setObjective(const NumericalMathFunction & objective)
{
  copyOnWrite();
  getImplementation()->setObjective(objective);
}

Bool OptimizationProblem::hasMultipleObjective() const
{
  return getImplementation()->hasMultipleObjective();
}

/* Equality constraint accessor */
NumericalMathFunction OptimizationProblem::getEqualityConstraint() const
{
  return getImplementation()->getEqualityConstraint();
}

void OptimizationProblem::setEqualityConstraint(const NumericalMathFunction & equalityConstraint)
{
  copyOnWrite();
  getImplementation()->setEqualityConstraint(equalityConstraint);
}

Bool OptimizationProblem::hasEqualityConstraint() const
{
  return getImplementation()->hasEqualityConstraint();
}

/* Inequality constraint accessor */
NumericalMathFunction OptimizationProblem::getInequalityConstraint() const
{
  return getImplementation()->getInequalityConstraint();
}

void OptimizationProblem::setInequalityConstraint(const NumericalMathFunction & inequalityConstraint)
{
  copyOnWrite();
  getImplementation()->setInequalityConstraint(inequalityConstraint);
}

Bool OptimizationProblem::hasInequalityConstraint() const
{
  return getImplementation()->hasInequalityConstraint();
}

/* Bounds accessor */
Interval OptimizationProblem::getBounds() const
{
  return getImplementation()->getBounds();
}

void OptimizationProblem::setBounds(const Interval & bounds)
{
  copyOnWrite();
  getImplementation()->setBounds(bounds);
}

Bool OptimizationProblem::hasBounds() const
{
  return getImplementation()->hasBounds();
}

/* Level function accessor */
NumericalMathFunction OptimizationProblem::getLevelFunction() const
{
  return getImplementation()->getLevelFunction();
}

void OptimizationProblem::setLevelFunction(const NumericalMathFunction & levelFunction)
{
  copyOnWrite();
  getImplementation()->setLevelFunction(levelFunction);
}

Bool OptimizationProblem::hasLevelFunction() const
{
  return getImplementation()->hasLevelFunction();
}

/* Level value accessor */
NumericalScalar OptimizationProblem::getLevelValue() const
{
  return getImplementation()->getLevelValue();
}

void OptimizationProblem::setLevelValue(NumericalScalar levelValue)
{
  getImplementation()->setLevelValue(levelValue);
}

/* Dimension accessor */
UnsignedInteger OptimizationProblem::getDimension() const
{
  return getImplementation()->getDimension();
}

/* Minimization accessor */
void OptimizationProblem::setMinimization(Bool minimization)
{
  copyOnWrite();
  getImplementation()->setMinimization(minimization);
}

Bool OptimizationProblem::isMinimization() const
{
  return getImplementation()->isMinimization();
}

/* String converter */
String OptimizationProblem::__repr__() const
{
  OSS oss(true);
  oss << "class=" << OptimizationProblem::GetClassName()
      << " implementation=" << getImplementation()->__repr__();
  return oss;
}

/* String converter */
String OptimizationProblem::__str__(const String & offset) const
{
  return __repr__();
}

END_NAMESPACE_OPENTURNS
