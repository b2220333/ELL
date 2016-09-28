////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     SignPredictor.h (predictors)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// utilities
#include "IArchivable.h"

// stl
#include <memory>

namespace emll
{
namespace predictors
{
    /// <summary> Wraps a predictor, typically an IPredictor(double), and exposes an IPredictor(bool)
    /// whose predictions are the sign bit of the original predictions. </summary>
    ///
    /// <typeparam name="PredictorType"> The internal predictor type. </typeparam>
    template <typename PredictorType>
    class SignPredictor : IPredictor<bool>, public utilities::IArchivable
    {
    public:
        /// <summary> Type of the data vector expected by this predictor type. </summary>
        using DataVectorType = typename PredictorType::DataVectorType;

        SignPredictor() = default;

        /// <summary> Constructs an instance of SignPredictor from an internal predictor. </summary>
        ///
        /// <param name="predictor"> The internal predictor. </param>
        SignPredictor(PredictorType predictor);

        SignPredictor(SignPredictor&&) = default;

        SignPredictor(const SignPredictor&) = default;

        /// <summary> Gets a reference to the internal predictor. </summary>
        ///
        /// <returns> A reference to the internal predictor. </returns>
        PredictorType& GetPredictor();

        /// <summary> Gets a const reference to the internal predictor. </summary>
        ///
        /// <returns> A const reference to the internal predictor. </returns>
        const PredictorType& GetPredictor() const;

        /// <summary> Returns the output of the predictor for a given example. </summary>
        ///
        /// <param name="example"> The data vector. </param>
        ///
        /// <returns> The prediction. </returns>
        bool Predict(const DataVectorType& dataVector) const;

        /// <summary> Adds an object's properties to an `Archiver` </summary>
        ///
        /// <param name="archiver"> The `Archiver` to add the values from the object to </param>
        void WriteToArchive(utilities::Archiver& archiver) const override;

        /// <summary> Sets the internal state of the object according to the archiver passed in </summary>
        ///
        /// <param name="archiver"> The `Archiver` to get state from </param>
        void ReadFromArchive(utilities::Unarchiver& archiver) override;

    private:
        PredictorType _predictor;
    };

    /// <summary> Makes a SignPredictor. </summary>
    ///
    /// <typeparam name="PredictorType"> Internal predictor type. </typeparam>
    /// <param name="predictor"> The internal predictor. </param>
    ///
    /// <returns> A SignPredictor </returns>
    template <typename PredictorType>
    SignPredictor<PredictorType> MakeSignPredictor(PredictorType predictor);
}
}

#include "../tcc/SignPredictor.tcc"