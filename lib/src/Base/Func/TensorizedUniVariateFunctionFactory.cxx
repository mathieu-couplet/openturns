//                                               -*- C++ -*-
/**
 *  @brief This is the tensorized function basis
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
#include "openturns/TensorizedUniVariateFunctionFactory.hxx"
#include "openturns/OSS.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/Exception.hxx"
#include "openturns/Indices.hxx"
#include "openturns/NumericalMathFunctionImplementation.hxx"
#include "openturns/ProductUniVariateFunctionEvaluationImplementation.hxx"
#include "openturns/ProductUniVariateFunctionGradientImplementation.hxx"
#include "openturns/ProductUniVariateFunctionHessianImplementation.hxx"

BEGIN_NAMESPACE_OPENTURNS



TEMPLATE_CLASSNAMEINIT(PersistentCollection<UniVariateFunctionFamily>);

static const Factory<PersistentCollection<UniVariateFunctionFamily> > Factory_PersistentCollection_UniVariateFunctionFamily;

CLASSNAMEINIT(TensorizedUniVariateFunctionFactory);

static const Factory<TensorizedUniVariateFunctionFactory> Factory_TensorizedUniVariateFunctionFactory;

typedef Collection<NumericalPoint> NumericalPointCollection;
typedef ProductUniVariateFunctionEvaluationImplementation::UniVariateFunctionCollection UniVariateFunctionCollection;

/* Default constructor */
TensorizedUniVariateFunctionFactory::TensorizedUniVariateFunctionFactory()
  : FunctionalBasisImplementation()
  , coll_()
  , phi_()
{
  // Nothing to do
}


/* Constructor */
TensorizedUniVariateFunctionFactory::TensorizedUniVariateFunctionFactory(const FunctionFamilyCollection & coll)
  : FunctionalBasisImplementation()
  , coll_(coll)
  , phi_(coll.getSize())
{
  // Nothing to do
}


/* Constructor */
TensorizedUniVariateFunctionFactory::TensorizedUniVariateFunctionFactory(const FunctionFamilyCollection & coll,
    const EnumerateFunction & phi)
  : FunctionalBasisImplementation(),
    coll_(coll),
    phi_(phi)
{
  if (coll.getSize() != phi.getDimension()) throw InvalidArgumentException(HERE) << "Error: the enumerate function must have a dimension equal to the collection size";
}


/* Virtual constructor */
TensorizedUniVariateFunctionFactory * TensorizedUniVariateFunctionFactory::clone() const
{
  return new TensorizedUniVariateFunctionFactory(*this);
}


/* Return the enumerate function that translate unidimensional indices into multidimensional indices */
EnumerateFunction TensorizedUniVariateFunctionFactory::getEnumerateFunction() const
{
  return phi_;
}

/* set the enumerate function that translate unidimensional indices into multidimensional indices */
void TensorizedUniVariateFunctionFactory::setEnumerateFunction(const EnumerateFunction & phi)
{
  phi_ = phi;
}

/* set the function familly collection */
void TensorizedUniVariateFunctionFactory::setFunctionFamilyCollection(const FunctionFamilyCollection & coll)
{
  coll_ = coll;
  if (coll.getSize() != phi_.getDimension())
  {
    setEnumerateFunction(EnumerateFunction(coll.getSize()));
  }
}

/* Build the NumericalMathFunction of the given index */
NumericalMathFunction TensorizedUniVariateFunctionFactory::build(const UnsignedInteger index) const
{
  // Compute the multi-indices using the EnumerateFunction
  const Indices indices(phi_(index));
  const UnsignedInteger size = indices.getSize();
  // Then build the collection of functions using the collection of factories
  UniVariateFunctionCollection functions(size);
  for (UnsignedInteger i = 0; i < size; ++ i)
  {
    functions[i] = coll_[i].build(indices[i]);
  }
  const Pointer<ProductUniVariateFunctionEvaluationImplementation> p_evaluation(ProductUniVariateFunctionEvaluationImplementation(functions).clone());
  return NumericalMathFunctionImplementation(p_evaluation,
         ProductUniVariateFunctionGradientImplementation(p_evaluation).clone(),
         ProductUniVariateFunctionHessianImplementation(p_evaluation).clone());
}


/* String converter */
String TensorizedUniVariateFunctionFactory::__repr__() const
{
  return OSS() << "class=" << getClassName()
         << " univariate function collection=" << coll_
         << " enumerate function=" << phi_;
}


/* Method save() stores the object through the StorageManager */
void TensorizedUniVariateFunctionFactory::save(Advocate & adv) const
{
  FunctionalBasisImplementation::save(adv);
  adv.saveAttribute( "coll_", coll_ );
  adv.saveAttribute( "phi_", phi_ );
}


/* Method load() reloads the object from the StorageManager */
void TensorizedUniVariateFunctionFactory::load(Advocate & adv)
{
  FunctionalBasisImplementation::load(adv);
  adv.loadAttribute( "coll_", coll_ );
  adv.loadAttribute( "phi_", phi_ );
}


END_NAMESPACE_OPENTURNS
