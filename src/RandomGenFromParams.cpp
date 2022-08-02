#include "RandomGenFromParams.hpp"

RandomGenFromParams::RandomGenFromParams(){fineTSprev = 0;}
RandomGenFromParams::~RandomGenFromParams(){}

void RandomGenFromParams::setMod(std::string sValue)
{
    this->nummod = stoi(sValue);
}

void RandomGenFromParams::setCh(std::string sValue)
{
    this->numch = stoi(sValue);
}

void RandomGenFromParams::setFMean(std::string sValue)
{

    this->fineTSIncMean = std::stod(sValue);

}

void RandomGenFromParams::setFSigma(std::string sValue)
{
    this->fineTSIncSigma = std::stod(sValue);
}

void RandomGenFromParams::setCLMean(std::string sValue)
{
    this->clMean = std::stod(sValue);
}

void RandomGenFromParams::setCLSigma(std::string sValue)
{
    this->clSigma = std::stod(sValue);
}

void RandomGenFromParams::setCSMean(std::string sValue)
{
    this->csMean = std::stod(sValue);
}

void RandomGenFromParams::setCSSigma(std::string sValue)
{
    this->csSigma = std::stod(sValue);
}

void RandomGenFromParams::setTreeDataGaus(TreeData *tdata, TRandom3 *rand_gen)
{
    tdata->Mod = rand_gen->Integer(this->nummod);
    tdata->Ch = rand_gen->Integer(this->numch);
    tdata->FineTS = fineTSprev + rand_gen->Gaus(this->fineTSIncMean, this->fineTSIncSigma);
    tdata->TimeStamp = tdata->FineTS/1000;
    tdata->ChargeLong = rand_gen->Gaus(this->clMean, this->clSigma);
    tdata->ChargeShort = rand_gen->Gaus(this->csMean, this->csSigma);
    tdata->Extras = 0;
    tdata -> RecordLength = 512;

    fineTSprev = tdata->FineTS;
}