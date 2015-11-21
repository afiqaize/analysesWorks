#!/bin/bash
### Utility for the template

python MCTemplates/getTemplatesFromMC.py --input tnp_mc_pp15bx25.root --output fitTemp_pp15bx25_et_eta.root --directory GsfElectronHLTTight --idprobe passingHLT --var1Name probe_et --var1Bins 25.,30.,35.,40.,45.,50.,65.,90.,135.,190.,250. --var2Name probe_eta --var2Bins -2.5,-2.1,-1.6,-1.4,-0.7,0.,0.7,1.4,1.6,2.1,2.5 --weightVarName puWgt

python MCTemplates/getTemplatesFromMC.py --input tnp_mc_pp15bx25.root --output fitTemp_pp15bx25_et.root --directory GsfElectronHLTTight --idprobe passingHLT --var1Name probe_et --var1Bins 25.,30.,35.,40.,45.,50.,65.,90.,135.,190.,250. --var2Name probe_eta --var2Bins -2.5,2.5 --weightVarName puWgt

python MCTemplates/getTemplatesFromMC.py --input tnp_mc_pp15bx25.root --output fitTemp_pp15bx25_eta.root --directory GsfElectronHLTTight --idprobe passingHLT --var1Name probe_et --var1Bins 25.,250. --var2Name probe_eta --var2Bins -2.5,-2.1,-1.6,-1.4,-0.7,0.,0.7,1.4,1.6,2.1,2.5 --weightVarName puWgt

python MCTemplates/getTemplatesFromMC.py --input tnp_mc_pp15bx25.root --output fitTemp_pp15bx25_evt.root --directory GsfElectronHLTTight --idprobe passingHLT --var1Name probe_et --var1Bins 25.,250. --var2Name probe_eta --var2Bins -2.5,2.5 --weightVarName puWgt

python MCTemplates/makeConfigForTemplates.py --idLabel pdf --outputFile fitPdf_pp15bx25_et_eta.py --templateFile fitTemp_pp15bx25_et_eta.root --var1Bins 25.,30.,35.,40.,45.,50.,65.,90.,135.,190.,250. --var2Bins -2.5,-2.1,-1.6,-1.4,-0.7,0.,0.7,1.4,1.6,2.1,2.5

python MCTemplates/makeConfigForTemplates.py --idLabel pdf --outputFile fitPdf_pp15bx25_et.py --templateFile fitTemp_pp15bx25_et.root --var1Bins  25.,30.,35.,40.,45.,50.,65.,90.,135.,190.,250. --var2Bins -2.5,2.5

python MCTemplates/makeConfigForTemplates.py --idLabel pdf --outputFile fitPdf_pp15bx25_eta.py --templateFile fitTemp_pp15bx25_eta.root --var1Bins 25.,250. --var2Bins -2.5,-2.1,-1.6,-1.4,-0.7,0.,0.7,1.4,1.6,2.1,2.5

python MCTemplates/makeConfigForTemplates.py --idLabel pdf --outputFile fitPdf_pp15bx25_evt.py --templateFile fitTemp_pp15bx25_evt.root --var1Bins 25.,250. --var2Bins -2.5,2.5
