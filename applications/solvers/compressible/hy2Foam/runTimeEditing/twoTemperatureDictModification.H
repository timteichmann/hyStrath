
if(thermo.twoTemperatureDictionary().subDict("thermalRelaxationModels").lookupOrDefault<bool>("applyChanges", false))
{
    //---------------------------------------------------------
    // Re-definition of the relaxation models
    //---------------------------------------------------------

    // Vibrational-Translational (V-T) energy transfer
    thermalRelaxModelVT.clear();

    if(not downgradeSingleT)
    {
        thermalRelaxModelVT = relaxationTimeModel::New
        (
            thermo,
            turbulence()
        );
    }

    // Vibrational-Vibrational (V-V) energy transfer
    thermalRelaxModelVV.clear();

    if(not(downgradeSingleT or downgradeSingleTv) and noSolvedVibEq > 1)
    {
        thermalRelaxModelVV = relaxationTimeModelVV::New
        (
            thermo,
            turbulence()
        );
    }

    // Heavy-particles - free electrons (h-e) energy transfer
    thermalRelaxModelHE.clear();

    if(not downgradeSingleT and containsElectrons)
    {
        thermalRelaxModelHE = relaxationTimeModelHE::New
        (
            thermo,
            turbulence()
        );
    }

    // Free-electrons - vibrational energy transfer
    thermalRelaxModeleV.clear();

    if(not(downgradeSingleT or downgradeSingleTv) and containsElectrons)
    {
        thermalRelaxModeleV = relaxationTimeModeleV::New
        (
            thermo,
            turbulence()
        );
    }

    thermo.twoTemperatureDictionary().subDict("thermalRelaxationModels").set<bool>("applyChanges", false);

    noSubRestart += 1;
}

