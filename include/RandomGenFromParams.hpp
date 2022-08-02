#ifndef RandomGenFromParams_hpp
#define RandomGenFromParams_hpp 1


#include "TRandom.h"
#include "TRandom3.h"
#include "TreeData.h"
#include <string>
#include <iostream>
#include <random>

class RandomGenFromParams
{
    public:
    RandomGenFromParams();
    ~RandomGenFromParams();

    int nummod = 0;//module number
    int numch = 0;//channel number
    Double_t fineTSIncMean = 0;//mean for the fineTS incrementor
    Double_t fineTSIncSigma = 0;//sigma for the fineTS incrementor
    double fineTSprev = 0;
    Double_t clMean = 0;//mean for the charge long gaus random
    Double_t clSigma = 0;//sigma for the charge long gaus random
    Double_t csMean = 0;//mean for the charge short gaus random
    Double_t csSigma = 0;//sigma for the charge short gaus random

    void setMod(std::string sValue);
    void setCh(std::string sValue);
    void setFMean(std::string sValue);
    void setFSigma(std::string sValue);
    void setCLMean(std::string sValue);
    void setCLSigma(std::string sValue);
    void setCSMean(std::string sValue);
    void setCSSigma(std::string sValue);
    void setTreeDataGaus(TreeData *tdata, TRandom3 *rand_gen);
};

#endif