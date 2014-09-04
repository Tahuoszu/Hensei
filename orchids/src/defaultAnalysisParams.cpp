//
//  defaultAnalysisParams.cpp
//  Orchids
//
//  Created by Antoine Bouchereau on 20/12/13.
//  Copyright (c) 2013 Antoine Bouchereau. All rights reserved.
//

#include "defaultAnalysisParams.h"

/**
 *  @brief Initialize default parameters for analysis
 */
analysis_params defaultAnalysisParams()
{
    analysis_params parameters;
    
    vector<ircamDescriptor_param> ircdesc_default_params;
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "ResampleTo", 22050));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "NormalizeSignal", 0));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "WindowType", "blackman"));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "SaveShortTermTMFeatures", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "SubstractMean", 0));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "AutoCorrelationCoeffs", 12));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "ReducedBands", 4));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "PerceptualBands", 24));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "MFCCs", 13));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "Harmonics", 20));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "F0MaxAnalysisFreq", 3000));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "F0MinFrequency", 200));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "F0MaxFrequency", 1000));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "F0AmpThreshold", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "F0AmplitudeModulation", 0));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "RolloffThreshold", 0.95));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "DeviationStopBand", 10));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "DecreaseThreshold", 0.4));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "NoiseThreshold", 0.15));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "ChromaFreqMinHz", 77));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "ChromaFreqMaxHz", 1500));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "ChromaResolution", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "ChromaNormmax", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "MedianFilterOrder", 5));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "MedianFilterNormalize", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("parameters", "DynamicMorfologicFeatures", 0));
    ircdesc_default_params.push_back(ircamDescriptor_param("standard", "WindowSize", 0.06));
    ircdesc_default_params.push_back(ircamDescriptor_param("standard", "HopSize", 0.01));
    ircdesc_default_params.push_back(ircamDescriptor_param("standard", "TextureWindowsFrames", -1));
    ircdesc_default_params.push_back(ircamDescriptor_param("standard", "TextureWindowsHopFrames", -1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "WindowSize", 0.1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "HopSize", 0.002));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "TextureWindowsFrames", -1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "TextureWindowsHopFrames", -1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "TemporalIncrease", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "TemporalDecrease", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "TemporalCentroid", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "EffectiveDuration", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "LogAttackTime", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "AmplitudeModulation", 1));
    ircdesc_default_params.push_back(ircamDescriptor_param("energy", "EnergyEnvelope", 1));
    
    parameters.irc_desc_params  = ircdesc_default_params;
    
    return parameters;
}
