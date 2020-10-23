import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("LOLK")

options = VarParsing('analysis')
options.register(
    "inputDir",
    "",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Input directory with inputs"
    )
options.register(
    "outputName",
    "",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output root filename w/o ext"
    )
options.register(
    "fileBase",
    "AToTT",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "File base name"
    )
options.parseArguments()

if (options.inputDir == ""):
    sys.exit("Directory to find input file where???")
else:
    InputDir = "file:/pnfs/desy.de/cms/tier2/store/user/afiqaize/samples80X/ahtt_gensim_211216/" + options.inputDir + "/"

if (options.outputName == ""):
    sys.exit("Output file not specified!")

process.load("Configuration.StandardSequences.Services_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.load('RecoJets.JetProducers.ak4GenJets_cfi')
process.load('RecoMET.Configuration.GenMETParticles_cff')
process.load('RecoMET.METProducers.genMetTrue_cfi')

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
)

readFiles = cms.untracked.vstring()
readFiles.extend( [InputDir + options.fileBase + "_GENSIM_1.root",
                   InputDir + options.fileBase + "_GENSIM_2.root",
                   InputDir + options.fileBase + "_GENSIM_3.root",
                   InputDir + options.fileBase + "_GENSIM_4.root",
                   InputDir + options.fileBase + "_GENSIM_5.root",
                   InputDir + options.fileBase + "_GENSIM_6.root",
                   InputDir + options.fileBase + "_GENSIM_7.root",
                   InputDir + options.fileBase + "_GENSIM_8.root",
                   InputDir + options.fileBase + "_GENSIM_9.root",
                   InputDir + options.fileBase + "_GENSIM_10.root",
                   InputDir + options.fileBase + "_GENSIM_11.root",
                   InputDir + options.fileBase + "_GENSIM_12.root",
                   InputDir + options.fileBase + "_GENSIM_13.root",
                   InputDir + options.fileBase + "_GENSIM_14.root",
                   InputDir + options.fileBase + "_GENSIM_15.root",
                   InputDir + options.fileBase + "_GENSIM_16.root",
                   InputDir + options.fileBase + "_GENSIM_17.root",
                   InputDir + options.fileBase + "_GENSIM_18.root",
                   InputDir + options.fileBase + "_GENSIM_19.root",
                   InputDir + options.fileBase + "_GENSIM_20.root",
                   InputDir + options.fileBase + "_GENSIM_21.root",
                   InputDir + options.fileBase + "_GENSIM_22.root",
                   InputDir + options.fileBase + "_GENSIM_23.root",
                   InputDir + options.fileBase + "_GENSIM_24.root",
                   InputDir + options.fileBase + "_GENSIM_25.root",
                   InputDir + options.fileBase + "_GENSIM_26.root",
                   InputDir + options.fileBase + "_GENSIM_27.root",
                   InputDir + options.fileBase + "_GENSIM_28.root",
                   InputDir + options.fileBase + "_GENSIM_29.root",
                   InputDir + options.fileBase + "_GENSIM_30.root",
                   InputDir + options.fileBase + "_GENSIM_31.root",
                   InputDir + options.fileBase + "_GENSIM_32.root",
                   InputDir + options.fileBase + "_GENSIM_33.root",
                   InputDir + options.fileBase + "_GENSIM_34.root",
                   InputDir + options.fileBase + "_GENSIM_35.root",
                   InputDir + options.fileBase + "_GENSIM_36.root",
                   InputDir + options.fileBase + "_GENSIM_37.root",
                   InputDir + options.fileBase + "_GENSIM_38.root",
                   InputDir + options.fileBase + "_GENSIM_39.root",
                   InputDir + options.fileBase + "_GENSIM_40.root",
                   InputDir + options.fileBase + "_GENSIM_41.root",
                   InputDir + options.fileBase + "_GENSIM_42.root",
                   InputDir + options.fileBase + "_GENSIM_43.root",
                   InputDir + options.fileBase + "_GENSIM_44.root",
                   InputDir + options.fileBase + "_GENSIM_45.root",
                   InputDir + options.fileBase + "_GENSIM_46.root",
                   InputDir + options.fileBase + "_GENSIM_47.root",
                   InputDir + options.fileBase + "_GENSIM_48.root",
                   InputDir + options.fileBase + "_GENSIM_49.root",
                   InputDir + options.fileBase + "_GENSIM_50.root",
                   InputDir + options.fileBase + "_GENSIM_51.root",
                   InputDir + options.fileBase + "_GENSIM_52.root",
                   InputDir + options.fileBase + "_GENSIM_53.root",
                   InputDir + options.fileBase + "_GENSIM_54.root",
                   InputDir + options.fileBase + "_GENSIM_55.root",
                   InputDir + options.fileBase + "_GENSIM_56.root",
                   InputDir + options.fileBase + "_GENSIM_57.root",
                   InputDir + options.fileBase + "_GENSIM_58.root",
                   InputDir + options.fileBase + "_GENSIM_59.root",
                   InputDir + options.fileBase + "_GENSIM_60.root",
                   InputDir + options.fileBase + "_GENSIM_61.root",
                   InputDir + options.fileBase + "_GENSIM_62.root",
                   InputDir + options.fileBase + "_GENSIM_63.root",
                   InputDir + options.fileBase + "_GENSIM_64.root",
                   InputDir + options.fileBase + "_GENSIM_65.root",
                   InputDir + options.fileBase + "_GENSIM_66.root",
                   InputDir + options.fileBase + "_GENSIM_67.root",
                   InputDir + options.fileBase + "_GENSIM_68.root",
                   InputDir + options.fileBase + "_GENSIM_69.root",
                   InputDir + options.fileBase + "_GENSIM_70.root",
                   InputDir + options.fileBase + "_GENSIM_71.root",
                   InputDir + options.fileBase + "_GENSIM_72.root",
                   InputDir + options.fileBase + "_GENSIM_73.root",
                   InputDir + options.fileBase + "_GENSIM_74.root",
                   InputDir + options.fileBase + "_GENSIM_75.root",
                   InputDir + options.fileBase + "_GENSIM_76.root",
                   InputDir + options.fileBase + "_GENSIM_77.root",
                   InputDir + options.fileBase + "_GENSIM_78.root",
                   InputDir + options.fileBase + "_GENSIM_79.root",
                   InputDir + options.fileBase + "_GENSIM_80.root",
                   InputDir + options.fileBase + "_GENSIM_81.root",
                   InputDir + options.fileBase + "_GENSIM_82.root",
                   InputDir + options.fileBase + "_GENSIM_83.root",
                   InputDir + options.fileBase + "_GENSIM_84.root",
                   InputDir + options.fileBase + "_GENSIM_85.root",
                   InputDir + options.fileBase + "_GENSIM_86.root",
                   InputDir + options.fileBase + "_GENSIM_87.root",
                   InputDir + options.fileBase + "_GENSIM_88.root",
                   InputDir + options.fileBase + "_GENSIM_89.root",
                   InputDir + options.fileBase + "_GENSIM_90.root",
                   InputDir + options.fileBase + "_GENSIM_91.root",
                   InputDir + options.fileBase + "_GENSIM_92.root",
                   InputDir + options.fileBase + "_GENSIM_93.root",
                   InputDir + options.fileBase + "_GENSIM_94.root",
                   InputDir + options.fileBase + "_GENSIM_95.root",
                   InputDir + options.fileBase + "_GENSIM_96.root",
                   InputDir + options.fileBase + "_GENSIM_97.root",
                   InputDir + options.fileBase + "_GENSIM_98.root",
                   InputDir + options.fileBase + "_GENSIM_99.root",
                   InputDir + options.fileBase + "_GENSIM_100.root",
                   InputDir + options.fileBase + "_GENSIM_101.root",
                   InputDir + options.fileBase + "_GENSIM_102.root",
                   InputDir + options.fileBase + "_GENSIM_103.root",
                   InputDir + options.fileBase + "_GENSIM_104.root",
                   InputDir + options.fileBase + "_GENSIM_105.root",
                   InputDir + options.fileBase + "_GENSIM_106.root",
                   InputDir + options.fileBase + "_GENSIM_107.root",
                   InputDir + options.fileBase + "_GENSIM_108.root",
                   InputDir + options.fileBase + "_GENSIM_109.root",
                   InputDir + options.fileBase + "_GENSIM_110.root",
                   InputDir + options.fileBase + "_GENSIM_111.root",
                   InputDir + options.fileBase + "_GENSIM_112.root",
                   InputDir + options.fileBase + "_GENSIM_113.root",
                   InputDir + options.fileBase + "_GENSIM_114.root",
                   InputDir + options.fileBase + "_GENSIM_115.root",
                   InputDir + options.fileBase + "_GENSIM_116.root",
                   InputDir + options.fileBase + "_GENSIM_117.root",
                   InputDir + options.fileBase + "_GENSIM_118.root",
                   InputDir + options.fileBase + "_GENSIM_119.root",
                   InputDir + options.fileBase + "_GENSIM_120.root",
                   InputDir + options.fileBase + "_GENSIM_121.root",
                   InputDir + options.fileBase + "_GENSIM_122.root",
                   InputDir + options.fileBase + "_GENSIM_123.root",
                   InputDir + options.fileBase + "_GENSIM_124.root",
                   InputDir + options.fileBase + "_GENSIM_125.root",
                   InputDir + options.fileBase + "_GENSIM_126.root",
                   InputDir + options.fileBase + "_GENSIM_127.root",
                   InputDir + options.fileBase + "_GENSIM_128.root",
                   InputDir + options.fileBase + "_GENSIM_129.root",
                   InputDir + options.fileBase + "_GENSIM_130.root",
                   InputDir + options.fileBase + "_GENSIM_131.root",
                   InputDir + options.fileBase + "_GENSIM_132.root",
                   InputDir + options.fileBase + "_GENSIM_133.root",
                   InputDir + options.fileBase + "_GENSIM_134.root",
                   InputDir + options.fileBase + "_GENSIM_135.root",
                   InputDir + options.fileBase + "_GENSIM_136.root",
                   InputDir + options.fileBase + "_GENSIM_137.root",
                   InputDir + options.fileBase + "_GENSIM_138.root",
                   InputDir + options.fileBase + "_GENSIM_139.root",
                   InputDir + options.fileBase + "_GENSIM_140.root",
                   InputDir + options.fileBase + "_GENSIM_141.root",
                   InputDir + options.fileBase + "_GENSIM_142.root",
                   InputDir + options.fileBase + "_GENSIM_143.root",
                   InputDir + options.fileBase + "_GENSIM_144.root",
                   InputDir + options.fileBase + "_GENSIM_145.root",
                   InputDir + options.fileBase + "_GENSIM_146.root",
                   InputDir + options.fileBase + "_GENSIM_147.root",
                   InputDir + options.fileBase + "_GENSIM_148.root",
                   InputDir + options.fileBase + "_GENSIM_149.root",
                   InputDir + options.fileBase + "_GENSIM_150.root",
                   InputDir + options.fileBase + "_GENSIM_151.root",
                   InputDir + options.fileBase + "_GENSIM_152.root",
                   InputDir + options.fileBase + "_GENSIM_153.root",
                   InputDir + options.fileBase + "_GENSIM_154.root",
                   InputDir + options.fileBase + "_GENSIM_155.root",
                   InputDir + options.fileBase + "_GENSIM_156.root",
                   InputDir + options.fileBase + "_GENSIM_157.root",
                   InputDir + options.fileBase + "_GENSIM_158.root",
                   InputDir + options.fileBase + "_GENSIM_159.root",
                   InputDir + options.fileBase + "_GENSIM_160.root",
                   InputDir + options.fileBase + "_GENSIM_161.root",
                   InputDir + options.fileBase + "_GENSIM_162.root",
                   InputDir + options.fileBase + "_GENSIM_163.root",
                   InputDir + options.fileBase + "_GENSIM_164.root",
                   InputDir + options.fileBase + "_GENSIM_165.root",
                   InputDir + options.fileBase + "_GENSIM_166.root",
                   InputDir + options.fileBase + "_GENSIM_167.root",
                   InputDir + options.fileBase + "_GENSIM_168.root",
                   InputDir + options.fileBase + "_GENSIM_169.root",
                   InputDir + options.fileBase + "_GENSIM_170.root",
                   InputDir + options.fileBase + "_GENSIM_171.root",
                   InputDir + options.fileBase + "_GENSIM_172.root",
                   InputDir + options.fileBase + "_GENSIM_173.root",
                   InputDir + options.fileBase + "_GENSIM_174.root",
                   InputDir + options.fileBase + "_GENSIM_175.root",
                   InputDir + options.fileBase + "_GENSIM_176.root",
                   InputDir + options.fileBase + "_GENSIM_177.root",
                   InputDir + options.fileBase + "_GENSIM_178.root",
                   InputDir + options.fileBase + "_GENSIM_179.root",
                   InputDir + options.fileBase + "_GENSIM_180.root",
                   InputDir + options.fileBase + "_GENSIM_181.root",
                   InputDir + options.fileBase + "_GENSIM_182.root",
                   InputDir + options.fileBase + "_GENSIM_183.root",
                   InputDir + options.fileBase + "_GENSIM_184.root",
                   InputDir + options.fileBase + "_GENSIM_185.root",
                   InputDir + options.fileBase + "_GENSIM_186.root",
                   InputDir + options.fileBase + "_GENSIM_187.root",
                   InputDir + options.fileBase + "_GENSIM_188.root",
                   InputDir + options.fileBase + "_GENSIM_189.root",
                   InputDir + options.fileBase + "_GENSIM_190.root",
                   InputDir + options.fileBase + "_GENSIM_191.root",
                   InputDir + options.fileBase + "_GENSIM_192.root",
                   InputDir + options.fileBase + "_GENSIM_193.root",
                   InputDir + options.fileBase + "_GENSIM_194.root",
                   InputDir + options.fileBase + "_GENSIM_195.root",
                   InputDir + options.fileBase + "_GENSIM_196.root",
                   InputDir + options.fileBase + "_GENSIM_197.root",
                   InputDir + options.fileBase + "_GENSIM_198.root",
                   InputDir + options.fileBase + "_GENSIM_199.root",
                   InputDir + options.fileBase + "_GENSIM_200.root",
                   InputDir + options.fileBase + "_GENSIM_201.root",
                   InputDir + options.fileBase + "_GENSIM_202.root",
                   InputDir + options.fileBase + "_GENSIM_203.root",
                   InputDir + options.fileBase + "_GENSIM_204.root",
                   InputDir + options.fileBase + "_GENSIM_205.root",
                   InputDir + options.fileBase + "_GENSIM_206.root",
                   InputDir + options.fileBase + "_GENSIM_207.root",
                   InputDir + options.fileBase + "_GENSIM_208.root",
                   InputDir + options.fileBase + "_GENSIM_209.root",
                   InputDir + options.fileBase + "_GENSIM_210.root",
                   InputDir + options.fileBase + "_GENSIM_211.root",
                   InputDir + options.fileBase + "_GENSIM_212.root",
                   InputDir + options.fileBase + "_GENSIM_213.root",
                   InputDir + options.fileBase + "_GENSIM_214.root",
                   InputDir + options.fileBase + "_GENSIM_215.root",
                   InputDir + options.fileBase + "_GENSIM_216.root",
                   InputDir + options.fileBase + "_GENSIM_217.root",
                   InputDir + options.fileBase + "_GENSIM_218.root",
                   InputDir + options.fileBase + "_GENSIM_219.root",
                   InputDir + options.fileBase + "_GENSIM_220.root",
                   InputDir + options.fileBase + "_GENSIM_221.root",
                   InputDir + options.fileBase + "_GENSIM_222.root",
                   InputDir + options.fileBase + "_GENSIM_223.root",
                   InputDir + options.fileBase + "_GENSIM_224.root",
                   InputDir + options.fileBase + "_GENSIM_225.root",
                   InputDir + options.fileBase + "_GENSIM_226.root",
                   InputDir + options.fileBase + "_GENSIM_227.root",
                   InputDir + options.fileBase + "_GENSIM_228.root",
                   InputDir + options.fileBase + "_GENSIM_229.root",
                   InputDir + options.fileBase + "_GENSIM_230.root",
                   InputDir + options.fileBase + "_GENSIM_231.root",
                   InputDir + options.fileBase + "_GENSIM_232.root",
                   InputDir + options.fileBase + "_GENSIM_233.root",
                   InputDir + options.fileBase + "_GENSIM_234.root",
                   InputDir + options.fileBase + "_GENSIM_235.root",
                   InputDir + options.fileBase + "_GENSIM_236.root",
                   InputDir + options.fileBase + "_GENSIM_237.root",
                   InputDir + options.fileBase + "_GENSIM_238.root",
                   InputDir + options.fileBase + "_GENSIM_239.root",
                   InputDir + options.fileBase + "_GENSIM_240.root",
                   InputDir + options.fileBase + "_GENSIM_241.root",
                   InputDir + options.fileBase + "_GENSIM_242.root",
                   InputDir + options.fileBase + "_GENSIM_243.root",
                   InputDir + options.fileBase + "_GENSIM_244.root",
                   InputDir + options.fileBase + "_GENSIM_245.root",
                   InputDir + options.fileBase + "_GENSIM_246.root",
                   InputDir + options.fileBase + "_GENSIM_247.root",
                   InputDir + options.fileBase + "_GENSIM_248.root",
                   InputDir + options.fileBase + "_GENSIM_249.root",
                   InputDir + options.fileBase + "_GENSIM_250.root",
                   InputDir + options.fileBase + "_GENSIM_251.root",
                   InputDir + options.fileBase + "_GENSIM_252.root",
                   InputDir + options.fileBase + "_GENSIM_253.root",
                   InputDir + options.fileBase + "_GENSIM_254.root",
                   InputDir + options.fileBase + "_GENSIM_255.root",
                   InputDir + options.fileBase + "_GENSIM_256.root",
                   InputDir + options.fileBase + "_GENSIM_257.root",
                   InputDir + options.fileBase + "_GENSIM_258.root",
                   InputDir + options.fileBase + "_GENSIM_259.root",
                   InputDir + options.fileBase + "_GENSIM_260.root",
                   InputDir + options.fileBase + "_GENSIM_261.root",
                   InputDir + options.fileBase + "_GENSIM_262.root",
                   InputDir + options.fileBase + "_GENSIM_263.root",
                   InputDir + options.fileBase + "_GENSIM_264.root",
                   InputDir + options.fileBase + "_GENSIM_265.root",
                   InputDir + options.fileBase + "_GENSIM_266.root",
                   InputDir + options.fileBase + "_GENSIM_267.root",
                   InputDir + options.fileBase + "_GENSIM_268.root",
                   InputDir + options.fileBase + "_GENSIM_269.root",
                   InputDir + options.fileBase + "_GENSIM_270.root",
                   InputDir + options.fileBase + "_GENSIM_271.root",
                   InputDir + options.fileBase + "_GENSIM_272.root",
                   InputDir + options.fileBase + "_GENSIM_273.root",
                   InputDir + options.fileBase + "_GENSIM_274.root",
                   InputDir + options.fileBase + "_GENSIM_275.root",
                   InputDir + options.fileBase + "_GENSIM_276.root",
                   InputDir + options.fileBase + "_GENSIM_277.root",
                   InputDir + options.fileBase + "_GENSIM_278.root",
                   InputDir + options.fileBase + "_GENSIM_279.root",
                   InputDir + options.fileBase + "_GENSIM_280.root",
                   InputDir + options.fileBase + "_GENSIM_281.root",
                   InputDir + options.fileBase + "_GENSIM_282.root",
                   InputDir + options.fileBase + "_GENSIM_283.root",
                   InputDir + options.fileBase + "_GENSIM_284.root",
                   InputDir + options.fileBase + "_GENSIM_285.root",
                   InputDir + options.fileBase + "_GENSIM_286.root",
                   InputDir + options.fileBase + "_GENSIM_287.root",
                   InputDir + options.fileBase + "_GENSIM_288.root",
                   InputDir + options.fileBase + "_GENSIM_289.root",
                   InputDir + options.fileBase + "_GENSIM_290.root",
                   InputDir + options.fileBase + "_GENSIM_291.root",
                   InputDir + options.fileBase + "_GENSIM_292.root",
                   InputDir + options.fileBase + "_GENSIM_293.root",
                   InputDir + options.fileBase + "_GENSIM_294.root",
                   InputDir + options.fileBase + "_GENSIM_295.root",
                   InputDir + options.fileBase + "_GENSIM_296.root",
                   InputDir + options.fileBase + "_GENSIM_297.root",
                   InputDir + options.fileBase + "_GENSIM_298.root",
                   InputDir + options.fileBase + "_GENSIM_299.root",
                   InputDir + options.fileBase + "_GENSIM_300.root",
                   InputDir + options.fileBase + "_GENSIM_301.root",
                   InputDir + options.fileBase + "_GENSIM_302.root",
                   InputDir + options.fileBase + "_GENSIM_303.root",
                   InputDir + options.fileBase + "_GENSIM_304.root",
                   InputDir + options.fileBase + "_GENSIM_305.root",
                   InputDir + options.fileBase + "_GENSIM_306.root",
                   InputDir + options.fileBase + "_GENSIM_307.root",
                   InputDir + options.fileBase + "_GENSIM_308.root",
                   InputDir + options.fileBase + "_GENSIM_309.root",
                   InputDir + options.fileBase + "_GENSIM_310.root",
                   InputDir + options.fileBase + "_GENSIM_311.root",
                   InputDir + options.fileBase + "_GENSIM_312.root",
                   InputDir + options.fileBase + "_GENSIM_313.root",
                   InputDir + options.fileBase + "_GENSIM_314.root",
                   InputDir + options.fileBase + "_GENSIM_315.root",
                   InputDir + options.fileBase + "_GENSIM_316.root",
                   InputDir + options.fileBase + "_GENSIM_317.root",
                   InputDir + options.fileBase + "_GENSIM_318.root",
                   InputDir + options.fileBase + "_GENSIM_319.root",
                   InputDir + options.fileBase + "_GENSIM_320.root",
                   InputDir + options.fileBase + "_GENSIM_321.root",
                   InputDir + options.fileBase + "_GENSIM_322.root",
                   InputDir + options.fileBase + "_GENSIM_323.root",
                   InputDir + options.fileBase + "_GENSIM_324.root",
                   InputDir + options.fileBase + "_GENSIM_325.root",
                   InputDir + options.fileBase + "_GENSIM_326.root",
                   InputDir + options.fileBase + "_GENSIM_327.root",
                   InputDir + options.fileBase + "_GENSIM_328.root",
                   InputDir + options.fileBase + "_GENSIM_329.root",
                   InputDir + options.fileBase + "_GENSIM_330.root",
                   InputDir + options.fileBase + "_GENSIM_331.root",
                   InputDir + options.fileBase + "_GENSIM_332.root",
                   InputDir + options.fileBase + "_GENSIM_333.root",
                   InputDir + options.fileBase + "_GENSIM_334.root",
                   InputDir + options.fileBase + "_GENSIM_335.root",
                   InputDir + options.fileBase + "_GENSIM_336.root",
                   InputDir + options.fileBase + "_GENSIM_337.root",
                   InputDir + options.fileBase + "_GENSIM_338.root",
                   InputDir + options.fileBase + "_GENSIM_339.root",
                   InputDir + options.fileBase + "_GENSIM_340.root",
                   InputDir + options.fileBase + "_GENSIM_341.root",
                   InputDir + options.fileBase + "_GENSIM_342.root",
                   InputDir + options.fileBase + "_GENSIM_343.root",
                   InputDir + options.fileBase + "_GENSIM_344.root",
                   InputDir + options.fileBase + "_GENSIM_345.root",
                   InputDir + options.fileBase + "_GENSIM_346.root",
                   InputDir + options.fileBase + "_GENSIM_347.root",
                   InputDir + options.fileBase + "_GENSIM_348.root",
                   InputDir + options.fileBase + "_GENSIM_349.root",
                   InputDir + options.fileBase + "_GENSIM_350.root",
                   InputDir + options.fileBase + "_GENSIM_351.root",
                   InputDir + options.fileBase + "_GENSIM_352.root",
                   InputDir + options.fileBase + "_GENSIM_353.root",
                   InputDir + options.fileBase + "_GENSIM_354.root",
                   InputDir + options.fileBase + "_GENSIM_355.root",
                   InputDir + options.fileBase + "_GENSIM_356.root",
                   InputDir + options.fileBase + "_GENSIM_357.root",
                   InputDir + options.fileBase + "_GENSIM_358.root",
                   InputDir + options.fileBase + "_GENSIM_359.root",
                   InputDir + options.fileBase + "_GENSIM_360.root",
                   InputDir + options.fileBase + "_GENSIM_361.root",
                   InputDir + options.fileBase + "_GENSIM_362.root",
                   InputDir + options.fileBase + "_GENSIM_363.root",
                   InputDir + options.fileBase + "_GENSIM_364.root",
                   InputDir + options.fileBase + "_GENSIM_365.root",
                   InputDir + options.fileBase + "_GENSIM_366.root",
                   InputDir + options.fileBase + "_GENSIM_367.root",
                   InputDir + options.fileBase + "_GENSIM_368.root",
                   InputDir + options.fileBase + "_GENSIM_369.root",
                   InputDir + options.fileBase + "_GENSIM_370.root",
                   InputDir + options.fileBase + "_GENSIM_371.root",
                   InputDir + options.fileBase + "_GENSIM_372.root",
                   InputDir + options.fileBase + "_GENSIM_373.root",
                   InputDir + options.fileBase + "_GENSIM_374.root",
                   InputDir + options.fileBase + "_GENSIM_375.root",
                   InputDir + options.fileBase + "_GENSIM_376.root",
                   InputDir + options.fileBase + "_GENSIM_377.root",
                   InputDir + options.fileBase + "_GENSIM_378.root",
                   InputDir + options.fileBase + "_GENSIM_379.root",
                   InputDir + options.fileBase + "_GENSIM_380.root",
                   InputDir + options.fileBase + "_GENSIM_381.root",
                   InputDir + options.fileBase + "_GENSIM_382.root",
                   InputDir + options.fileBase + "_GENSIM_383.root",
                   InputDir + options.fileBase + "_GENSIM_384.root",
                   InputDir + options.fileBase + "_GENSIM_385.root",
                   InputDir + options.fileBase + "_GENSIM_386.root",
                   InputDir + options.fileBase + "_GENSIM_387.root",
                   InputDir + options.fileBase + "_GENSIM_388.root",
                   InputDir + options.fileBase + "_GENSIM_389.root",
                   InputDir + options.fileBase + "_GENSIM_390.root",
                   InputDir + options.fileBase + "_GENSIM_391.root",
                   InputDir + options.fileBase + "_GENSIM_392.root",
                   InputDir + options.fileBase + "_GENSIM_393.root",
                   InputDir + options.fileBase + "_GENSIM_394.root",
                   InputDir + options.fileBase + "_GENSIM_395.root",
                   InputDir + options.fileBase + "_GENSIM_396.root",
                   InputDir + options.fileBase + "_GENSIM_397.root",
                   InputDir + options.fileBase + "_GENSIM_398.root",
                   InputDir + options.fileBase + "_GENSIM_399.root",
                   InputDir + options.fileBase + "_GENSIM_400.root",
] )

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = readFiles
)

process.ttSel = cms.EDAnalyzer("ttSelector",
        outputName = cms.string( options.outputName + ".root" ),
        decayType = cms.int32( 2 ),
        includeTau = cms.bool( True ),
        doKinSel = cms.bool( False ),
        kinSelection = cms.PSet(jetPtCut = cms.double( 30. ),
                                jetEtaCut = cms.double( 4.5 ),
                                lepPtCut  = cms.double( 20. ),
                                lepEtaCut = cms.double( 3.0 )
                            ), 
        )
process.p = cms.Path(process.genParticlesForJets + process.ak4GenJets + process.genMETParticles + process.genMetTrue + process.ttSel)

                                        