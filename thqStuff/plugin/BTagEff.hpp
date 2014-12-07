/***
BTagEff.hpp
Author  Afiq A. Anuar
Summary This plugin saves jet information from a particular event selection and saves them based
        on flavor and whether they are tagged, from which the tagging efficiency can be obtained
***/

#pragma once

#include <Plugin.hpp>
#include <PECReaderPlugin.hpp>
#include <BTagger.hpp>

#include <TFile.h>
#include <TH2.h>
#include <TH1.h>

#include <string>

class BTagEff: public Plugin
{
    public:
        /// Constructor
        BTagEff(std::string const &outDirectory, BTagger const &bTagger);

    public:
/**
* \brief Creates a newly-initialized copy
* Consult documentation of the overriden method for details.
*/
        Plugin *Clone() const;
        
/**
* \brief Notifies this that a dataset has been opened
* Consult documentation of the overriden method for details.
*/
        void BeginRun(Dataset const &dataset);
        
/**
* \brief Notifies this that a dataset has been closed
* Consult documentation of the overriden method for details.
*/
        void EndRun();
        
/**
* \brief Processes the current event
* Consult documentation of the overriden method for details.
*/
        bool ProcessEvent();

    private:
        /// Pointer to PECReaderPlugin
        PECReaderPlugin const *reader;
        
        /// An object to perform b-tagging
        BTagger const &bTagger;
        
        /// Directory to store output files
        std::string outDirectory;

        /// Vector of all jets in an event
        std::vector<Jet> allJets;

        /// Other relevant physics parameters
        Float_t MET;
        
        /// Current output file
        TFile *file;
        
        /// Numerator and Denominator histograms
        /// b hists
        TH2D *PtEta_Num_b_T, *PtEta_Den_b_T;
        TH1D *Pt_Num_b_T, *Pt_Den_b_T, *Eta_Num_b_T, *Eta_Den_b_T;

        /// c hists
        TH2D *PtEta_Num_c_T, *PtEta_Den_c_T;
        TH1D *Pt_Num_c_T, *Pt_Den_c_T, *Eta_Num_c_T, *Eta_Den_c_T;

        /// uds hists
        TH2D *PtEta_Num_uds_T, *PtEta_Den_uds_T;
        TH1D *Pt_Num_uds_T, *Pt_Den_uds_T, *Eta_Num_uds_T, *Eta_Den_uds_T;

        /// gluon hists
        TH2D *PtEta_Num_g_T, *PtEta_Den_g_T;
        TH1D *Pt_Num_g_T, *Pt_Den_g_T, *Eta_Num_g_T, *Eta_Den_g_T;

        /// Historgram parameters
        Int_t ptBin, etaBin;
        Float_t ptMin, ptMax, etaMin, etaMax;

};
