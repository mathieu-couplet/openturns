//                                               -*- C++ -*-
/**
 *  @brief Factory for Histogram distribution
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
#ifndef OPENTURNS_HISTOGRAMFACTORY_HXX
#define OPENTURNS_HISTOGRAMFACTORY_HXX

#include "openturns/OTprivate.hxx"
#include "openturns/DistributionFactoryImplementation.hxx"
#include "openturns/Histogram.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class HistogramFactory
 */
class OT_API HistogramFactory
  : public DistributionFactoryImplementation
{
  CLASSNAME;
public:

  /** Default constructor */
  HistogramFactory();

  /** Virtual constructor */
  virtual HistogramFactory * clone() const;

  /* Here is the interface that all derived class must implement */
  using DistributionFactoryImplementation::build;

  Implementation build(const NumericalSample & sample) const;
  Implementation build(const NumericalSample & sample,
		       const NumericalScalar bandwidth) const;
  Implementation build(const NumericalSample & sample,
		       const UnsignedInteger binNumber) const;
  Implementation build() const;
  Histogram buildAsHistogram(const NumericalSample & sample) const;
  Histogram buildAsHistogram(const NumericalSample & sample,
		       const NumericalScalar bandwidth) const;
  Histogram buildAsHistogram(const NumericalSample & sample,
		       const UnsignedInteger binNumber) const;
  Histogram buildAsHistogram() const;

  /** Compute the bandwidth according to Silverman's rule */
  NumericalScalar computeSilvermanBandwidth(const NumericalSample & sample,
					    const Bool useQuantile = true) const;

}; /* class HistogramFactory */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_HISTOGRAMFACTORY_HXX */
