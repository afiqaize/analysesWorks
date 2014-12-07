#!/bin/env python

"""
    Draws two ROC from different tests for comparison.
    When using the script, do not forget to set environment for modern Python.
    Example usage: python discrROC.py test337 test344 THvsTTbar_Global_BFGS '#337 and #344'
"""

import sys
import os
import ROOT


# Check the arguments
if len(sys.argv) != 5:
    print 'Usage: discrROC infoFileName01 infoFileName02 MLPName Title'
    sys.exit(1)

infoFileName01 = sys.argv[1]
infoFileName02 = sys.argv[2]
mlpName = sys.argv[3]
title = sys.argv[4]

# Some style settings
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetStripDecimals(False)
ROOT.gStyle.SetErrorX(0.)

FileName01 = infoFileName01 + '.root'
FileName02 = infoFileName02 + '.root'

# Open the TMVA file
infoFile01 = ROOT.TFile(FileName01)
if infoFile01.IsZombie():
    print 'Cannot open file "' + infoFileName01 + '.root"'
    sys.exit(1)

infoFile02 = ROOT.TFile(FileName02)
if infoFile02.IsZombie():
    print 'Cannot open file "' + infoFileName02 + '.root"'
    sys.exit(1)


# Create directory to store output
outDirectory = 'ROC_figs/'
if not os.path.exists(outDirectory):
    os.makedirs(outDirectory)


# Create a canvas to draw
canvas = ROOT.TCanvas('', '', 1500, 1200)
canvas.SetGrid()

# Get the ROC curves (a TH1) from the files and draw it
roc01 = infoFile01.Get('Method_MLP/' + mlpName + '/MVA_' + mlpName + '_rejBvsS')
if not roc01:
    print 'Cannot find histogram "Method_MLP/' + mlpName + '/MVA_' + mlpName + '_rejBvsS" in ' +\
     'the source file.'
    sys.exit(1)

roc02 = infoFile02.Get('Method_MLP/' + mlpName + '/MVA_' + mlpName + '_rejBvsS')
if not roc02:
    print 'Cannot find histogram "Method_MLP/' + mlpName + '/MVA_' + mlpName + '_rejBvsS" in ' +\
     'the source file.'
    sys.exit(1)

roc01.SetTitle(title + ';Signal selection efficiency;Background rejection efficiency')
roc01.SetMinimum(0.)
roc01.SetLineWidth(2)
roc01.SetLineColor(ROOT.kRed)
roc01.Draw('c')

roc02.SetLineWidth(2)
roc02.SetLineColor(ROOT.kBlue)
roc02.Draw('csame')

# Create a legend
legend = ROOT.TLegend(0.72, 0.73, 0.89, 0.89)
legend.SetFillColor(ROOT.kWhite)

legend.AddEntry(roc01, infoFileName01);
legend.AddEntry(roc02, infoFileName02);

legend.Draw()

canvas.Print(outDirectory + infoFileName01 + '_' + infoFileName02 + '_roc.pdf')
canvas.Print(outDirectory + infoFileName01 + '_' + infoFileName02 + '_roc.png')
canvas.Print(outDirectory + infoFileName01 + '_' + infoFileName02 + '_roc.C')
