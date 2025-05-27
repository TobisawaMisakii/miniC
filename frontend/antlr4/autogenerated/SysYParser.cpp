
// Generated from SysY.g4 by ANTLR 4.12.0


#include "SysYVisitor.h"

#include "SysYParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SysYParserStaticData final {
  SysYParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SysYParserStaticData(const SysYParserStaticData&) = delete;
  SysYParserStaticData(SysYParserStaticData&&) = delete;
  SysYParserStaticData& operator=(const SysYParserStaticData&) = delete;
  SysYParserStaticData& operator=(SysYParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sysyParserOnceFlag;
SysYParserStaticData *sysyParserStaticData = nullptr;

void sysyParserInitialize() {
  assert(sysyParserStaticData == nullptr);
  auto staticData = std::make_unique<SysYParserStaticData>(
    std::vector<std::string>{
      "compileUnit", "macroDecl", "decl", "constDecl", "basicType", "constDef", 
      "constInitVal", "varDecl", "varDef", "initVal", "funcDef", "funcType", 
      "funcFParams", "funcFParam", "block", "blockItem", "stmt", "exp", 
      "cond", "lVal", "primaryExp", "number", "unaryExp", "unaryOp", "funcRParams", 
      "mulExp", "addExp", "relExp", "eqExp", "lAndExp", "lOrExp", "constExp"
    },
    std::vector<std::string>{
      "", "'#define'", "'const'", "','", "';'", "'int'", "'float'", "'['", 
      "']'", "'='", "'{'", "'}'", "'('", "')'", "'void'", "'if'", "'else'", 
      "'while'", "'break'", "'continue'", "'return'", "'+'", "'-'", "'!'", 
      "'*'", "'/'", "'%'", "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", 
      "'&&'", "'||'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "Ident", "IntConst", "DecimalConst", "OctalConst", "HexadecimalConst", 
      "HexadecimalPrefix", "NonzeroDigit", "Digit", "OctalDigit", "HexadecimalDigit", 
      "FloatConst", "WS", "COMMENT", "BLOCK_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,48,372,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,1,0,1,0,1,0,5,0,68,8,0,10,0,12,0,71,
  	9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,2,1,2,3,2,81,8,2,1,3,1,3,1,3,1,3,1,3,5,
  	3,88,8,3,10,3,12,3,91,9,3,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,5,102,
  	8,5,10,5,12,5,105,9,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,5,6,115,8,6,10,
  	6,12,6,118,9,6,3,6,120,8,6,1,6,3,6,123,8,6,1,7,1,7,1,7,1,7,5,7,129,8,
  	7,10,7,12,7,132,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,5,8,141,8,8,10,8,12,8,
  	144,9,8,1,8,1,8,1,8,1,8,1,8,5,8,151,8,8,10,8,12,8,154,9,8,1,8,1,8,3,8,
  	158,8,8,1,9,1,9,1,9,1,9,1,9,5,9,165,8,9,10,9,12,9,168,9,9,3,9,170,8,9,
  	1,9,3,9,173,8,9,1,10,1,10,1,10,1,10,3,10,179,8,10,1,10,1,10,1,10,1,11,
  	1,11,1,12,1,12,1,12,5,12,189,8,12,10,12,12,12,192,9,12,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,5,13,202,8,13,10,13,12,13,205,9,13,3,13,207,
  	8,13,1,14,1,14,5,14,211,8,14,10,14,12,14,214,9,14,1,14,1,14,1,15,1,15,
  	3,15,220,8,15,1,16,1,16,1,16,1,16,1,16,1,16,3,16,228,8,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,239,8,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,253,8,16,1,16,3,16,256,8,16,
  	1,17,1,17,1,18,1,18,1,19,1,19,1,19,1,19,1,19,5,19,267,8,19,10,19,12,19,
  	270,9,19,1,20,1,20,1,20,1,20,1,20,1,20,3,20,278,8,20,1,21,1,21,1,22,1,
  	22,1,22,1,22,3,22,286,8,22,1,22,1,22,1,22,1,22,3,22,292,8,22,1,23,1,23,
  	1,24,1,24,1,24,5,24,299,8,24,10,24,12,24,302,9,24,1,25,1,25,1,25,1,25,
  	1,25,1,25,5,25,310,8,25,10,25,12,25,313,9,25,1,26,1,26,1,26,1,26,1,26,
  	1,26,5,26,321,8,26,10,26,12,26,324,9,26,1,27,1,27,1,27,1,27,1,27,1,27,
  	5,27,332,8,27,10,27,12,27,335,9,27,1,28,1,28,1,28,1,28,1,28,1,28,5,28,
  	343,8,28,10,28,12,28,346,9,28,1,29,1,29,1,29,1,29,1,29,1,29,5,29,354,
  	8,29,10,29,12,29,357,9,29,1,30,1,30,1,30,1,30,1,30,1,30,5,30,365,8,30,
  	10,30,12,30,368,9,30,1,31,1,31,1,31,0,6,50,52,54,56,58,60,32,0,2,4,6,
  	8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,
  	56,58,60,62,0,8,1,0,5,6,2,0,5,6,14,14,2,0,36,36,45,45,1,0,21,23,1,0,24,
  	26,1,0,21,22,1,0,27,30,1,0,31,32,384,0,69,1,0,0,0,2,74,1,0,0,0,4,80,1,
  	0,0,0,6,82,1,0,0,0,8,94,1,0,0,0,10,96,1,0,0,0,12,122,1,0,0,0,14,124,1,
  	0,0,0,16,157,1,0,0,0,18,172,1,0,0,0,20,174,1,0,0,0,22,183,1,0,0,0,24,
  	185,1,0,0,0,26,193,1,0,0,0,28,208,1,0,0,0,30,219,1,0,0,0,32,255,1,0,0,
  	0,34,257,1,0,0,0,36,259,1,0,0,0,38,261,1,0,0,0,40,277,1,0,0,0,42,279,
  	1,0,0,0,44,291,1,0,0,0,46,293,1,0,0,0,48,295,1,0,0,0,50,303,1,0,0,0,52,
  	314,1,0,0,0,54,325,1,0,0,0,56,336,1,0,0,0,58,347,1,0,0,0,60,358,1,0,0,
  	0,62,369,1,0,0,0,64,68,3,2,1,0,65,68,3,4,2,0,66,68,3,20,10,0,67,64,1,
  	0,0,0,67,65,1,0,0,0,67,66,1,0,0,0,68,71,1,0,0,0,69,67,1,0,0,0,69,70,1,
  	0,0,0,70,72,1,0,0,0,71,69,1,0,0,0,72,73,5,0,0,1,73,1,1,0,0,0,74,75,5,
  	1,0,0,75,76,5,35,0,0,76,77,5,36,0,0,77,3,1,0,0,0,78,81,3,6,3,0,79,81,
  	3,14,7,0,80,78,1,0,0,0,80,79,1,0,0,0,81,5,1,0,0,0,82,83,5,2,0,0,83,84,
  	3,8,4,0,84,89,3,10,5,0,85,86,5,3,0,0,86,88,3,10,5,0,87,85,1,0,0,0,88,
  	91,1,0,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,92,1,0,0,0,91,89,1,0,0,0,92,
  	93,5,4,0,0,93,7,1,0,0,0,94,95,7,0,0,0,95,9,1,0,0,0,96,103,5,35,0,0,97,
  	98,5,7,0,0,98,99,3,62,31,0,99,100,5,8,0,0,100,102,1,0,0,0,101,97,1,0,
  	0,0,102,105,1,0,0,0,103,101,1,0,0,0,103,104,1,0,0,0,104,106,1,0,0,0,105,
  	103,1,0,0,0,106,107,5,9,0,0,107,108,3,12,6,0,108,11,1,0,0,0,109,123,3,
  	62,31,0,110,119,5,10,0,0,111,116,3,12,6,0,112,113,5,3,0,0,113,115,3,12,
  	6,0,114,112,1,0,0,0,115,118,1,0,0,0,116,114,1,0,0,0,116,117,1,0,0,0,117,
  	120,1,0,0,0,118,116,1,0,0,0,119,111,1,0,0,0,119,120,1,0,0,0,120,121,1,
  	0,0,0,121,123,5,11,0,0,122,109,1,0,0,0,122,110,1,0,0,0,123,13,1,0,0,0,
  	124,125,3,8,4,0,125,130,3,16,8,0,126,127,5,3,0,0,127,129,3,16,8,0,128,
  	126,1,0,0,0,129,132,1,0,0,0,130,128,1,0,0,0,130,131,1,0,0,0,131,133,1,
  	0,0,0,132,130,1,0,0,0,133,134,5,4,0,0,134,15,1,0,0,0,135,142,5,35,0,0,
  	136,137,5,7,0,0,137,138,3,62,31,0,138,139,5,8,0,0,139,141,1,0,0,0,140,
  	136,1,0,0,0,141,144,1,0,0,0,142,140,1,0,0,0,142,143,1,0,0,0,143,158,1,
  	0,0,0,144,142,1,0,0,0,145,152,5,35,0,0,146,147,5,7,0,0,147,148,3,62,31,
  	0,148,149,5,8,0,0,149,151,1,0,0,0,150,146,1,0,0,0,151,154,1,0,0,0,152,
  	150,1,0,0,0,152,153,1,0,0,0,153,155,1,0,0,0,154,152,1,0,0,0,155,156,5,
  	9,0,0,156,158,3,18,9,0,157,135,1,0,0,0,157,145,1,0,0,0,158,17,1,0,0,0,
  	159,173,3,34,17,0,160,169,5,10,0,0,161,166,3,18,9,0,162,163,5,3,0,0,163,
  	165,3,18,9,0,164,162,1,0,0,0,165,168,1,0,0,0,166,164,1,0,0,0,166,167,
  	1,0,0,0,167,170,1,0,0,0,168,166,1,0,0,0,169,161,1,0,0,0,169,170,1,0,0,
  	0,170,171,1,0,0,0,171,173,5,11,0,0,172,159,1,0,0,0,172,160,1,0,0,0,173,
  	19,1,0,0,0,174,175,3,22,11,0,175,176,5,35,0,0,176,178,5,12,0,0,177,179,
  	3,24,12,0,178,177,1,0,0,0,178,179,1,0,0,0,179,180,1,0,0,0,180,181,5,13,
  	0,0,181,182,3,28,14,0,182,21,1,0,0,0,183,184,7,1,0,0,184,23,1,0,0,0,185,
  	190,3,26,13,0,186,187,5,3,0,0,187,189,3,26,13,0,188,186,1,0,0,0,189,192,
  	1,0,0,0,190,188,1,0,0,0,190,191,1,0,0,0,191,25,1,0,0,0,192,190,1,0,0,
  	0,193,194,3,8,4,0,194,206,5,35,0,0,195,196,5,7,0,0,196,203,5,8,0,0,197,
  	198,5,7,0,0,198,199,3,34,17,0,199,200,5,8,0,0,200,202,1,0,0,0,201,197,
  	1,0,0,0,202,205,1,0,0,0,203,201,1,0,0,0,203,204,1,0,0,0,204,207,1,0,0,
  	0,205,203,1,0,0,0,206,195,1,0,0,0,206,207,1,0,0,0,207,27,1,0,0,0,208,
  	212,5,10,0,0,209,211,3,30,15,0,210,209,1,0,0,0,211,214,1,0,0,0,212,210,
  	1,0,0,0,212,213,1,0,0,0,213,215,1,0,0,0,214,212,1,0,0,0,215,216,5,11,
  	0,0,216,29,1,0,0,0,217,220,3,4,2,0,218,220,3,32,16,0,219,217,1,0,0,0,
  	219,218,1,0,0,0,220,31,1,0,0,0,221,222,3,38,19,0,222,223,5,9,0,0,223,
  	224,3,34,17,0,224,225,5,4,0,0,225,256,1,0,0,0,226,228,3,34,17,0,227,226,
  	1,0,0,0,227,228,1,0,0,0,228,229,1,0,0,0,229,256,5,4,0,0,230,256,3,28,
  	14,0,231,232,5,15,0,0,232,233,5,12,0,0,233,234,3,36,18,0,234,235,5,13,
  	0,0,235,238,3,32,16,0,236,237,5,16,0,0,237,239,3,32,16,0,238,236,1,0,
  	0,0,238,239,1,0,0,0,239,256,1,0,0,0,240,241,5,17,0,0,241,242,5,12,0,0,
  	242,243,3,36,18,0,243,244,5,13,0,0,244,245,3,32,16,0,245,256,1,0,0,0,
  	246,247,5,18,0,0,247,256,5,4,0,0,248,249,5,19,0,0,249,256,5,4,0,0,250,
  	252,5,20,0,0,251,253,3,34,17,0,252,251,1,0,0,0,252,253,1,0,0,0,253,254,
  	1,0,0,0,254,256,5,4,0,0,255,221,1,0,0,0,255,227,1,0,0,0,255,230,1,0,0,
  	0,255,231,1,0,0,0,255,240,1,0,0,0,255,246,1,0,0,0,255,248,1,0,0,0,255,
  	250,1,0,0,0,256,33,1,0,0,0,257,258,3,52,26,0,258,35,1,0,0,0,259,260,3,
  	60,30,0,260,37,1,0,0,0,261,268,5,35,0,0,262,263,5,7,0,0,263,264,3,34,
  	17,0,264,265,5,8,0,0,265,267,1,0,0,0,266,262,1,0,0,0,267,270,1,0,0,0,
  	268,266,1,0,0,0,268,269,1,0,0,0,269,39,1,0,0,0,270,268,1,0,0,0,271,272,
  	5,12,0,0,272,273,3,34,17,0,273,274,5,13,0,0,274,278,1,0,0,0,275,278,3,
  	38,19,0,276,278,3,42,21,0,277,271,1,0,0,0,277,275,1,0,0,0,277,276,1,0,
  	0,0,278,41,1,0,0,0,279,280,7,2,0,0,280,43,1,0,0,0,281,292,3,40,20,0,282,
  	283,5,35,0,0,283,285,5,12,0,0,284,286,3,48,24,0,285,284,1,0,0,0,285,286,
  	1,0,0,0,286,287,1,0,0,0,287,292,5,13,0,0,288,289,3,46,23,0,289,290,3,
  	44,22,0,290,292,1,0,0,0,291,281,1,0,0,0,291,282,1,0,0,0,291,288,1,0,0,
  	0,292,45,1,0,0,0,293,294,7,3,0,0,294,47,1,0,0,0,295,300,3,34,17,0,296,
  	297,5,3,0,0,297,299,3,34,17,0,298,296,1,0,0,0,299,302,1,0,0,0,300,298,
  	1,0,0,0,300,301,1,0,0,0,301,49,1,0,0,0,302,300,1,0,0,0,303,304,6,25,-1,
  	0,304,305,3,44,22,0,305,311,1,0,0,0,306,307,10,1,0,0,307,308,7,4,0,0,
  	308,310,3,44,22,0,309,306,1,0,0,0,310,313,1,0,0,0,311,309,1,0,0,0,311,
  	312,1,0,0,0,312,51,1,0,0,0,313,311,1,0,0,0,314,315,6,26,-1,0,315,316,
  	3,50,25,0,316,322,1,0,0,0,317,318,10,1,0,0,318,319,7,5,0,0,319,321,3,
  	50,25,0,320,317,1,0,0,0,321,324,1,0,0,0,322,320,1,0,0,0,322,323,1,0,0,
  	0,323,53,1,0,0,0,324,322,1,0,0,0,325,326,6,27,-1,0,326,327,3,52,26,0,
  	327,333,1,0,0,0,328,329,10,1,0,0,329,330,7,6,0,0,330,332,3,52,26,0,331,
  	328,1,0,0,0,332,335,1,0,0,0,333,331,1,0,0,0,333,334,1,0,0,0,334,55,1,
  	0,0,0,335,333,1,0,0,0,336,337,6,28,-1,0,337,338,3,54,27,0,338,344,1,0,
  	0,0,339,340,10,1,0,0,340,341,7,7,0,0,341,343,3,54,27,0,342,339,1,0,0,
  	0,343,346,1,0,0,0,344,342,1,0,0,0,344,345,1,0,0,0,345,57,1,0,0,0,346,
  	344,1,0,0,0,347,348,6,29,-1,0,348,349,3,56,28,0,349,355,1,0,0,0,350,351,
  	10,1,0,0,351,352,5,33,0,0,352,354,3,56,28,0,353,350,1,0,0,0,354,357,1,
  	0,0,0,355,353,1,0,0,0,355,356,1,0,0,0,356,59,1,0,0,0,357,355,1,0,0,0,
  	358,359,6,30,-1,0,359,360,3,58,29,0,360,366,1,0,0,0,361,362,10,1,0,0,
  	362,363,5,34,0,0,363,365,3,58,29,0,364,361,1,0,0,0,365,368,1,0,0,0,366,
  	364,1,0,0,0,366,367,1,0,0,0,367,61,1,0,0,0,368,366,1,0,0,0,369,370,3,
  	52,26,0,370,63,1,0,0,0,36,67,69,80,89,103,116,119,122,130,142,152,157,
  	166,169,172,178,190,203,206,212,219,227,238,252,255,268,277,285,291,300,
  	311,322,333,344,355,366
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sysyParserStaticData = staticData.release();
}

}

SysYParser::SysYParser(TokenStream *input) : SysYParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

SysYParser::SysYParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  SysYParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *sysyParserStaticData->atn, sysyParserStaticData->decisionToDFA, sysyParserStaticData->sharedContextCache, options);
}

SysYParser::~SysYParser() {
  delete _interpreter;
}

const atn::ATN& SysYParser::getATN() const {
  return *sysyParserStaticData->atn;
}

std::string SysYParser::getGrammarFileName() const {
  return "SysY.g4";
}

const std::vector<std::string>& SysYParser::getRuleNames() const {
  return sysyParserStaticData->ruleNames;
}

const dfa::Vocabulary& SysYParser::getVocabulary() const {
  return sysyParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SysYParser::getSerializedATN() const {
  return sysyParserStaticData->serializedATN;
}


//----------------- CompileUnitContext ------------------------------------------------------------------

SysYParser::CompileUnitContext::CompileUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::CompileUnitContext::EOF() {
  return getToken(SysYParser::EOF, 0);
}

std::vector<SysYParser::MacroDeclContext *> SysYParser::CompileUnitContext::macroDecl() {
  return getRuleContexts<SysYParser::MacroDeclContext>();
}

SysYParser::MacroDeclContext* SysYParser::CompileUnitContext::macroDecl(size_t i) {
  return getRuleContext<SysYParser::MacroDeclContext>(i);
}

std::vector<SysYParser::DeclContext *> SysYParser::CompileUnitContext::decl() {
  return getRuleContexts<SysYParser::DeclContext>();
}

SysYParser::DeclContext* SysYParser::CompileUnitContext::decl(size_t i) {
  return getRuleContext<SysYParser::DeclContext>(i);
}

std::vector<SysYParser::FuncDefContext *> SysYParser::CompileUnitContext::funcDef() {
  return getRuleContexts<SysYParser::FuncDefContext>();
}

SysYParser::FuncDefContext* SysYParser::CompileUnitContext::funcDef(size_t i) {
  return getRuleContext<SysYParser::FuncDefContext>(i);
}


size_t SysYParser::CompileUnitContext::getRuleIndex() const {
  return SysYParser::RuleCompileUnit;
}


std::any SysYParser::CompileUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitCompileUnit(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::CompileUnitContext* SysYParser::compileUnit() {
  CompileUnitContext *_localctx = _tracker.createInstance<CompileUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, SysYParser::RuleCompileUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16486) != 0)) {
      setState(67);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(64);
        macroDecl();
        break;
      }

      case 2: {
        setState(65);
        decl();
        break;
      }

      case 3: {
        setState(66);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(71);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(72);
    match(SysYParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MacroDeclContext ------------------------------------------------------------------

SysYParser::MacroDeclContext::MacroDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::MacroDeclContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

tree::TerminalNode* SysYParser::MacroDeclContext::IntConst() {
  return getToken(SysYParser::IntConst, 0);
}


size_t SysYParser::MacroDeclContext::getRuleIndex() const {
  return SysYParser::RuleMacroDecl;
}


std::any SysYParser::MacroDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitMacroDecl(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::MacroDeclContext* SysYParser::macroDecl() {
  MacroDeclContext *_localctx = _tracker.createInstance<MacroDeclContext>(_ctx, getState());
  enterRule(_localctx, 2, SysYParser::RuleMacroDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    match(SysYParser::T__0);
    setState(75);
    match(SysYParser::Ident);
    setState(76);
    match(SysYParser::IntConst);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

SysYParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::ConstDeclContext* SysYParser::DeclContext::constDecl() {
  return getRuleContext<SysYParser::ConstDeclContext>(0);
}

SysYParser::VarDeclContext* SysYParser::DeclContext::varDecl() {
  return getRuleContext<SysYParser::VarDeclContext>(0);
}


size_t SysYParser::DeclContext::getRuleIndex() const {
  return SysYParser::RuleDecl;
}


std::any SysYParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::DeclContext* SysYParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 4, SysYParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(80);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__1: {
        enterOuterAlt(_localctx, 1);
        setState(78);
        constDecl();
        break;
      }

      case SysYParser::T__4:
      case SysYParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(79);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

SysYParser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::BasicTypeContext* SysYParser::ConstDeclContext::basicType() {
  return getRuleContext<SysYParser::BasicTypeContext>(0);
}

std::vector<SysYParser::ConstDefContext *> SysYParser::ConstDeclContext::constDef() {
  return getRuleContexts<SysYParser::ConstDefContext>();
}

SysYParser::ConstDefContext* SysYParser::ConstDeclContext::constDef(size_t i) {
  return getRuleContext<SysYParser::ConstDefContext>(i);
}


size_t SysYParser::ConstDeclContext::getRuleIndex() const {
  return SysYParser::RuleConstDecl;
}


std::any SysYParser::ConstDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitConstDecl(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ConstDeclContext* SysYParser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, SysYParser::RuleConstDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(SysYParser::T__1);
    setState(83);
    basicType();
    setState(84);
    constDef();
    setState(89);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__2) {
      setState(85);
      match(SysYParser::T__2);
      setState(86);
      constDef();
      setState(91);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(92);
    match(SysYParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicTypeContext ------------------------------------------------------------------

SysYParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::BasicTypeContext::getRuleIndex() const {
  return SysYParser::RuleBasicType;
}


std::any SysYParser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::BasicTypeContext* SysYParser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 8, SysYParser::RuleBasicType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    _la = _input->LA(1);
    if (!(_la == SysYParser::T__4

    || _la == SysYParser::T__5)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDefContext ------------------------------------------------------------------

SysYParser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::ConstDefContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

SysYParser::ConstInitValContext* SysYParser::ConstDefContext::constInitVal() {
  return getRuleContext<SysYParser::ConstInitValContext>(0);
}

std::vector<SysYParser::ConstExpContext *> SysYParser::ConstDefContext::constExp() {
  return getRuleContexts<SysYParser::ConstExpContext>();
}

SysYParser::ConstExpContext* SysYParser::ConstDefContext::constExp(size_t i) {
  return getRuleContext<SysYParser::ConstExpContext>(i);
}


size_t SysYParser::ConstDefContext::getRuleIndex() const {
  return SysYParser::RuleConstDef;
}


std::any SysYParser::ConstDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitConstDef(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ConstDefContext* SysYParser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 10, SysYParser::RuleConstDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(SysYParser::Ident);
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__6) {
      setState(97);
      match(SysYParser::T__6);
      setState(98);
      constExp();
      setState(99);
      match(SysYParser::T__7);
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(106);
    match(SysYParser::T__8);
    setState(107);
    constInitVal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValContext ------------------------------------------------------------------

SysYParser::ConstInitValContext::ConstInitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::ConstInitValContext::getRuleIndex() const {
  return SysYParser::RuleConstInitVal;
}

void SysYParser::ConstInitValContext::copyFrom(ConstInitValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SingleConstantInitContext ------------------------------------------------------------------

SysYParser::ConstExpContext* SysYParser::SingleConstantInitContext::constExp() {
  return getRuleContext<SysYParser::ConstExpContext>(0);
}

SysYParser::SingleConstantInitContext::SingleConstantInitContext(ConstInitValContext *ctx) { copyFrom(ctx); }


std::any SysYParser::SingleConstantInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitSingleConstantInit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayConstantInitContext ------------------------------------------------------------------

std::vector<SysYParser::ConstInitValContext *> SysYParser::ArrayConstantInitContext::constInitVal() {
  return getRuleContexts<SysYParser::ConstInitValContext>();
}

SysYParser::ConstInitValContext* SysYParser::ArrayConstantInitContext::constInitVal(size_t i) {
  return getRuleContext<SysYParser::ConstInitValContext>(i);
}

SysYParser::ArrayConstantInitContext::ArrayConstantInitContext(ConstInitValContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ArrayConstantInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitArrayConstantInit(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::ConstInitValContext* SysYParser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 12, SysYParser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(122);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__11:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::T__22:
      case SysYParser::Ident:
      case SysYParser::IntConst:
      case SysYParser::FloatConst: {
        _localctx = _tracker.createInstance<SysYParser::SingleConstantInitContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(109);
        constExp();
        break;
      }

      case SysYParser::T__9: {
        _localctx = _tracker.createInstance<SysYParser::ArrayConstantInitContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(110);
        match(SysYParser::T__9);
        setState(119);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 35287465989120) != 0)) {
          setState(111);
          constInitVal();
          setState(116);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYParser::T__2) {
            setState(112);
            match(SysYParser::T__2);
            setState(113);
            constInitVal();
            setState(118);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(121);
        match(SysYParser::T__10);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

SysYParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::BasicTypeContext* SysYParser::VarDeclContext::basicType() {
  return getRuleContext<SysYParser::BasicTypeContext>(0);
}

std::vector<SysYParser::VarDefContext *> SysYParser::VarDeclContext::varDef() {
  return getRuleContexts<SysYParser::VarDefContext>();
}

SysYParser::VarDefContext* SysYParser::VarDeclContext::varDef(size_t i) {
  return getRuleContext<SysYParser::VarDefContext>(i);
}


size_t SysYParser::VarDeclContext::getRuleIndex() const {
  return SysYParser::RuleVarDecl;
}


std::any SysYParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::VarDeclContext* SysYParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 14, SysYParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    basicType();
    setState(125);
    varDef();
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__2) {
      setState(126);
      match(SysYParser::T__2);
      setState(127);
      varDef();
      setState(132);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(133);
    match(SysYParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

SysYParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::VarDefContext::getRuleIndex() const {
  return SysYParser::RuleVarDef;
}

void SysYParser::VarDefContext::copyFrom(VarDefContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SimpleVarDefContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::SimpleVarDefContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

std::vector<SysYParser::ConstExpContext *> SysYParser::SimpleVarDefContext::constExp() {
  return getRuleContexts<SysYParser::ConstExpContext>();
}

SysYParser::ConstExpContext* SysYParser::SimpleVarDefContext::constExp(size_t i) {
  return getRuleContext<SysYParser::ConstExpContext>(i);
}

SysYParser::SimpleVarDefContext::SimpleVarDefContext(VarDefContext *ctx) { copyFrom(ctx); }


std::any SysYParser::SimpleVarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitSimpleVarDef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InitializedVarDefContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::InitializedVarDefContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

SysYParser::InitValContext* SysYParser::InitializedVarDefContext::initVal() {
  return getRuleContext<SysYParser::InitValContext>(0);
}

std::vector<SysYParser::ConstExpContext *> SysYParser::InitializedVarDefContext::constExp() {
  return getRuleContexts<SysYParser::ConstExpContext>();
}

SysYParser::ConstExpContext* SysYParser::InitializedVarDefContext::constExp(size_t i) {
  return getRuleContext<SysYParser::ConstExpContext>(i);
}

SysYParser::InitializedVarDefContext::InitializedVarDefContext(VarDefContext *ctx) { copyFrom(ctx); }


std::any SysYParser::InitializedVarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitInitializedVarDef(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::VarDefContext* SysYParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 16, SysYParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(157);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::SimpleVarDefContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(135);
      match(SysYParser::Ident);
      setState(142);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__6) {
        setState(136);
        match(SysYParser::T__6);
        setState(137);
        constExp();
        setState(138);
        match(SysYParser::T__7);
        setState(144);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::InitializedVarDefContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(145);
      match(SysYParser::Ident);
      setState(152);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__6) {
        setState(146);
        match(SysYParser::T__6);
        setState(147);
        constExp();
        setState(148);
        match(SysYParser::T__7);
        setState(154);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(155);
      match(SysYParser::T__8);
      setState(156);
      initVal();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitValContext ------------------------------------------------------------------

SysYParser::InitValContext::InitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::InitValContext::getRuleIndex() const {
  return SysYParser::RuleInitVal;
}

void SysYParser::InitValContext::copyFrom(InitValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ArrayVarInitContext ------------------------------------------------------------------

std::vector<SysYParser::InitValContext *> SysYParser::ArrayVarInitContext::initVal() {
  return getRuleContexts<SysYParser::InitValContext>();
}

SysYParser::InitValContext* SysYParser::ArrayVarInitContext::initVal(size_t i) {
  return getRuleContext<SysYParser::InitValContext>(i);
}

SysYParser::ArrayVarInitContext::ArrayVarInitContext(InitValContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ArrayVarInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitArrayVarInit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SingleVarInitContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::SingleVarInitContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::SingleVarInitContext::SingleVarInitContext(InitValContext *ctx) { copyFrom(ctx); }


std::any SysYParser::SingleVarInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitSingleVarInit(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::InitValContext* SysYParser::initVal() {
  InitValContext *_localctx = _tracker.createInstance<InitValContext>(_ctx, getState());
  enterRule(_localctx, 18, SysYParser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(172);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__11:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::T__22:
      case SysYParser::Ident:
      case SysYParser::IntConst:
      case SysYParser::FloatConst: {
        _localctx = _tracker.createInstance<SysYParser::SingleVarInitContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(159);
        exp();
        break;
      }

      case SysYParser::T__9: {
        _localctx = _tracker.createInstance<SysYParser::ArrayVarInitContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(160);
        match(SysYParser::T__9);
        setState(169);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 35287465989120) != 0)) {
          setState(161);
          initVal();
          setState(166);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYParser::T__2) {
            setState(162);
            match(SysYParser::T__2);
            setState(163);
            initVal();
            setState(168);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(171);
        match(SysYParser::T__10);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

SysYParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::FuncTypeContext* SysYParser::FuncDefContext::funcType() {
  return getRuleContext<SysYParser::FuncTypeContext>(0);
}

tree::TerminalNode* SysYParser::FuncDefContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

SysYParser::BlockContext* SysYParser::FuncDefContext::block() {
  return getRuleContext<SysYParser::BlockContext>(0);
}

SysYParser::FuncFParamsContext* SysYParser::FuncDefContext::funcFParams() {
  return getRuleContext<SysYParser::FuncFParamsContext>(0);
}


size_t SysYParser::FuncDefContext::getRuleIndex() const {
  return SysYParser::RuleFuncDef;
}


std::any SysYParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncDefContext* SysYParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 20, SysYParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(174);
    funcType();
    setState(175);
    match(SysYParser::Ident);
    setState(176);
    match(SysYParser::T__11);
    setState(178);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::T__4

    || _la == SysYParser::T__5) {
      setState(177);
      funcFParams();
    }
    setState(180);
    match(SysYParser::T__12);
    setState(181);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

SysYParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::FuncTypeContext::getRuleIndex() const {
  return SysYParser::RuleFuncType;
}


std::any SysYParser::FuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncType(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncTypeContext* SysYParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 22, SysYParser::RuleFuncType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16480) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamsContext ------------------------------------------------------------------

SysYParser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::FuncFParamContext *> SysYParser::FuncFParamsContext::funcFParam() {
  return getRuleContexts<SysYParser::FuncFParamContext>();
}

SysYParser::FuncFParamContext* SysYParser::FuncFParamsContext::funcFParam(size_t i) {
  return getRuleContext<SysYParser::FuncFParamContext>(i);
}


size_t SysYParser::FuncFParamsContext::getRuleIndex() const {
  return SysYParser::RuleFuncFParams;
}


std::any SysYParser::FuncFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncFParams(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncFParamsContext* SysYParser::funcFParams() {
  FuncFParamsContext *_localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
  enterRule(_localctx, 24, SysYParser::RuleFuncFParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(185);
    funcFParam();
    setState(190);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__2) {
      setState(186);
      match(SysYParser::T__2);
      setState(187);
      funcFParam();
      setState(192);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

SysYParser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::BasicTypeContext* SysYParser::FuncFParamContext::basicType() {
  return getRuleContext<SysYParser::BasicTypeContext>(0);
}

tree::TerminalNode* SysYParser::FuncFParamContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

std::vector<SysYParser::ExpContext *> SysYParser::FuncFParamContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::FuncFParamContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}


size_t SysYParser::FuncFParamContext::getRuleIndex() const {
  return SysYParser::RuleFuncFParam;
}


std::any SysYParser::FuncFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncFParam(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncFParamContext* SysYParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 26, SysYParser::RuleFuncFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    basicType();
    setState(194);
    match(SysYParser::Ident);
    setState(206);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::T__6) {
      setState(195);
      match(SysYParser::T__6);
      setState(196);
      match(SysYParser::T__7);
      setState(203);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__6) {
        setState(197);
        match(SysYParser::T__6);
        setState(198);
        exp();
        setState(199);
        match(SysYParser::T__7);
        setState(205);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

SysYParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::BlockItemContext *> SysYParser::BlockContext::blockItem() {
  return getRuleContexts<SysYParser::BlockItemContext>();
}

SysYParser::BlockItemContext* SysYParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<SysYParser::BlockItemContext>(i);
}


size_t SysYParser::BlockContext::getRuleIndex() const {
  return SysYParser::RuleBlock;
}


std::any SysYParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::BlockContext* SysYParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 28, SysYParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    match(SysYParser::T__9);
    setState(212);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 35287467988084) != 0)) {
      setState(209);
      blockItem();
      setState(214);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(215);
    match(SysYParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

SysYParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::BlockItemContext::getRuleIndex() const {
  return SysYParser::RuleBlockItem;
}

void SysYParser::BlockItemContext::copyFrom(BlockItemContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StatementBlockItemContext ------------------------------------------------------------------

SysYParser::StmtContext* SysYParser::StatementBlockItemContext::stmt() {
  return getRuleContext<SysYParser::StmtContext>(0);
}

SysYParser::StatementBlockItemContext::StatementBlockItemContext(BlockItemContext *ctx) { copyFrom(ctx); }


std::any SysYParser::StatementBlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitStatementBlockItem(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeclarationBlockItemContext ------------------------------------------------------------------

SysYParser::DeclContext* SysYParser::DeclarationBlockItemContext::decl() {
  return getRuleContext<SysYParser::DeclContext>(0);
}

SysYParser::DeclarationBlockItemContext::DeclarationBlockItemContext(BlockItemContext *ctx) { copyFrom(ctx); }


std::any SysYParser::DeclarationBlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitDeclarationBlockItem(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::BlockItemContext* SysYParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 30, SysYParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(219);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__1:
      case SysYParser::T__4:
      case SysYParser::T__5: {
        _localctx = _tracker.createInstance<SysYParser::DeclarationBlockItemContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(217);
        decl();
        break;
      }

      case SysYParser::T__3:
      case SysYParser::T__9:
      case SysYParser::T__11:
      case SysYParser::T__14:
      case SysYParser::T__16:
      case SysYParser::T__17:
      case SysYParser::T__18:
      case SysYParser::T__19:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::T__22:
      case SysYParser::Ident:
      case SysYParser::IntConst:
      case SysYParser::FloatConst: {
        _localctx = _tracker.createInstance<SysYParser::StatementBlockItemContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(218);
        stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

SysYParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::StmtContext::getRuleIndex() const {
  return SysYParser::RuleStmt;
}

void SysYParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- WhileStatementContext ------------------------------------------------------------------

SysYParser::CondContext* SysYParser::WhileStatementContext::cond() {
  return getRuleContext<SysYParser::CondContext>(0);
}

SysYParser::StmtContext* SysYParser::WhileStatementContext::stmt() {
  return getRuleContext<SysYParser::StmtContext>(0);
}

SysYParser::WhileStatementContext::WhileStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentStatementContext ------------------------------------------------------------------

SysYParser::LValContext* SysYParser::AssignmentStatementContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

SysYParser::ExpContext* SysYParser::AssignmentStatementContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::AssignmentStatementContext::AssignmentStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::AssignmentStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitAssignmentStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NestedBlockStatementContext ------------------------------------------------------------------

SysYParser::BlockContext* SysYParser::NestedBlockStatementContext::block() {
  return getRuleContext<SysYParser::BlockContext>(0);
}

SysYParser::NestedBlockStatementContext::NestedBlockStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::NestedBlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitNestedBlockStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStatementContext ------------------------------------------------------------------

SysYParser::BreakStatementContext::BreakStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpressionStatementContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::ExpressionStatementContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::ExpressionStatementContext::ExpressionStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStatementContext ------------------------------------------------------------------

SysYParser::ContinueStatementContext::ContinueStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStatementContext ------------------------------------------------------------------

SysYParser::CondContext* SysYParser::IfStatementContext::cond() {
  return getRuleContext<SysYParser::CondContext>(0);
}

std::vector<SysYParser::StmtContext *> SysYParser::IfStatementContext::stmt() {
  return getRuleContexts<SysYParser::StmtContext>();
}

SysYParser::StmtContext* SysYParser::IfStatementContext::stmt(size_t i) {
  return getRuleContext<SysYParser::StmtContext>(i);
}

SysYParser::IfStatementContext::IfStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStatementContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::ReturnStatementContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::ReturnStatementContext::ReturnStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::StmtContext* SysYParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 32, SysYParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(255);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::AssignmentStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(221);
      lVal();
      setState(222);
      match(SysYParser::T__8);
      setState(223);
      exp();
      setState(224);
      match(SysYParser::T__3);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(227);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 35287465988096) != 0)) {
        setState(226);
        exp();
      }
      setState(229);
      match(SysYParser::T__3);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::NestedBlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(230);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SysYParser::IfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(231);
      match(SysYParser::T__14);
      setState(232);
      match(SysYParser::T__11);
      setState(233);
      cond();
      setState(234);
      match(SysYParser::T__12);
      setState(235);
      stmt();
      setState(238);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(236);
        match(SysYParser::T__15);
        setState(237);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SysYParser::WhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(240);
      match(SysYParser::T__16);
      setState(241);
      match(SysYParser::T__11);
      setState(242);
      cond();
      setState(243);
      match(SysYParser::T__12);
      setState(244);
      stmt();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SysYParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(246);
      match(SysYParser::T__17);
      setState(247);
      match(SysYParser::T__3);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SysYParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(248);
      match(SysYParser::T__18);
      setState(249);
      match(SysYParser::T__3);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<SysYParser::ReturnStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(250);
      match(SysYParser::T__19);
      setState(252);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 35287465988096) != 0)) {
        setState(251);
        exp();
      }
      setState(254);
      match(SysYParser::T__3);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

SysYParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::AddExpContext* SysYParser::ExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}


size_t SysYParser::ExpContext::getRuleIndex() const {
  return SysYParser::RuleExp;
}


std::any SysYParser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ExpContext* SysYParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 34, SysYParser::RuleExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(257);
    addExp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

SysYParser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::LOrExpContext* SysYParser::CondContext::lOrExp() {
  return getRuleContext<SysYParser::LOrExpContext>(0);
}


size_t SysYParser::CondContext::getRuleIndex() const {
  return SysYParser::RuleCond;
}


std::any SysYParser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::CondContext* SysYParser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 36, SysYParser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(259);
    lOrExp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

SysYParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::LValContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

std::vector<SysYParser::ExpContext *> SysYParser::LValContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::LValContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}


size_t SysYParser::LValContext::getRuleIndex() const {
  return SysYParser::RuleLVal;
}


std::any SysYParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::LValContext* SysYParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 38, SysYParser::RuleLVal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(261);
    match(SysYParser::Ident);
    setState(268);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(262);
        match(SysYParser::T__6);
        setState(263);
        exp();
        setState(264);
        match(SysYParser::T__7); 
      }
      setState(270);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpContext ------------------------------------------------------------------

SysYParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::PrimaryExpContext::getRuleIndex() const {
  return SysYParser::RulePrimaryExp;
}

void SysYParser::PrimaryExpContext::copyFrom(PrimaryExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LeftValueExpressionContext ------------------------------------------------------------------

SysYParser::LValContext* SysYParser::LeftValueExpressionContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

SysYParser::LeftValueExpressionContext::LeftValueExpressionContext(PrimaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::LeftValueExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLeftValueExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberExpressionContext ------------------------------------------------------------------

SysYParser::NumberContext* SysYParser::NumberExpressionContext::number() {
  return getRuleContext<SysYParser::NumberContext>(0);
}

SysYParser::NumberExpressionContext::NumberExpressionContext(PrimaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::NumberExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitNumberExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GroupedExpressionContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::GroupedExpressionContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::GroupedExpressionContext::GroupedExpressionContext(PrimaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::GroupedExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitGroupedExpression(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::PrimaryExpContext* SysYParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 40, SysYParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(277);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__11: {
        _localctx = _tracker.createInstance<SysYParser::GroupedExpressionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(271);
        match(SysYParser::T__11);
        setState(272);
        exp();
        setState(273);
        match(SysYParser::T__12);
        break;
      }

      case SysYParser::Ident: {
        _localctx = _tracker.createInstance<SysYParser::LeftValueExpressionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(275);
        lVal();
        break;
      }

      case SysYParser::IntConst:
      case SysYParser::FloatConst: {
        _localctx = _tracker.createInstance<SysYParser::NumberExpressionContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(276);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

SysYParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::NumberContext::IntConst() {
  return getToken(SysYParser::IntConst, 0);
}

tree::TerminalNode* SysYParser::NumberContext::FloatConst() {
  return getToken(SysYParser::FloatConst, 0);
}


size_t SysYParser::NumberContext::getRuleIndex() const {
  return SysYParser::RuleNumber;
}


std::any SysYParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::NumberContext* SysYParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 42, SysYParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(279);
    _la = _input->LA(1);
    if (!(_la == SysYParser::IntConst

    || _la == SysYParser::FloatConst)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpContext ------------------------------------------------------------------

SysYParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::UnaryExpContext::getRuleIndex() const {
  return SysYParser::RuleUnaryExp;
}

void SysYParser::UnaryExpContext::copyFrom(UnaryExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryOperatorExpressionContext ------------------------------------------------------------------

SysYParser::UnaryOpContext* SysYParser::UnaryOperatorExpressionContext::unaryOp() {
  return getRuleContext<SysYParser::UnaryOpContext>(0);
}

SysYParser::UnaryExpContext* SysYParser::UnaryOperatorExpressionContext::unaryExp() {
  return getRuleContext<SysYParser::UnaryExpContext>(0);
}

SysYParser::UnaryOperatorExpressionContext::UnaryOperatorExpressionContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::UnaryOperatorExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitUnaryOperatorExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryUnaryExpressionContext ------------------------------------------------------------------

SysYParser::PrimaryExpContext* SysYParser::PrimaryUnaryExpressionContext::primaryExp() {
  return getRuleContext<SysYParser::PrimaryExpContext>(0);
}

SysYParser::PrimaryUnaryExpressionContext::PrimaryUnaryExpressionContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::PrimaryUnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitPrimaryUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::FunctionCallContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

SysYParser::FuncRParamsContext* SysYParser::FunctionCallContext::funcRParams() {
  return getRuleContext<SysYParser::FuncRParamsContext>(0);
}

SysYParser::FunctionCallContext::FunctionCallContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::UnaryExpContext* SysYParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 44, SysYParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(291);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::PrimaryUnaryExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(281);
      primaryExp();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::FunctionCallContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(282);
      match(SysYParser::Ident);
      setState(283);
      match(SysYParser::T__11);
      setState(285);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 35287465988096) != 0)) {
        setState(284);
        funcRParams();
      }
      setState(287);
      match(SysYParser::T__12);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::UnaryOperatorExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(288);
      unaryOp();
      setState(289);
      unaryExp();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOpContext ------------------------------------------------------------------

SysYParser::UnaryOpContext::UnaryOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::UnaryOpContext::getRuleIndex() const {
  return SysYParser::RuleUnaryOp;
}


std::any SysYParser::UnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitUnaryOp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::UnaryOpContext* SysYParser::unaryOp() {
  UnaryOpContext *_localctx = _tracker.createInstance<UnaryOpContext>(_ctx, getState());
  enterRule(_localctx, 46, SysYParser::RuleUnaryOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 14680064) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamsContext ------------------------------------------------------------------

SysYParser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::ExpContext *> SysYParser::FuncRParamsContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::FuncRParamsContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}


size_t SysYParser::FuncRParamsContext::getRuleIndex() const {
  return SysYParser::RuleFuncRParams;
}


std::any SysYParser::FuncRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncRParams(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncRParamsContext* SysYParser::funcRParams() {
  FuncRParamsContext *_localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
  enterRule(_localctx, 48, SysYParser::RuleFuncRParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    exp();
    setState(300);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__2) {
      setState(296);
      match(SysYParser::T__2);
      setState(297);
      exp();
      setState(302);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpContext ------------------------------------------------------------------

SysYParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::UnaryExpContext* SysYParser::MulExpContext::unaryExp() {
  return getRuleContext<SysYParser::UnaryExpContext>(0);
}

SysYParser::MulExpContext* SysYParser::MulExpContext::mulExp() {
  return getRuleContext<SysYParser::MulExpContext>(0);
}


size_t SysYParser::MulExpContext::getRuleIndex() const {
  return SysYParser::RuleMulExp;
}


std::any SysYParser::MulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitMulExp(this);
  else
    return visitor->visitChildren(this);
}


SysYParser::MulExpContext* SysYParser::mulExp() {
   return mulExp(0);
}

SysYParser::MulExpContext* SysYParser::mulExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, parentState);
  SysYParser::MulExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, SysYParser::RuleMulExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(304);
    unaryExp();
    _ctx->stop = _input->LT(-1);
    setState(311);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MulExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMulExp);
        setState(306);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(307);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 117440512) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(308);
        unaryExp(); 
      }
      setState(313);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AddExpContext ------------------------------------------------------------------

SysYParser::AddExpContext::AddExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::MulExpContext* SysYParser::AddExpContext::mulExp() {
  return getRuleContext<SysYParser::MulExpContext>(0);
}

SysYParser::AddExpContext* SysYParser::AddExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}


size_t SysYParser::AddExpContext::getRuleIndex() const {
  return SysYParser::RuleAddExp;
}


std::any SysYParser::AddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitAddExp(this);
  else
    return visitor->visitChildren(this);
}


SysYParser::AddExpContext* SysYParser::addExp() {
   return addExp(0);
}

SysYParser::AddExpContext* SysYParser::addExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::AddExpContext *_localctx = _tracker.createInstance<AddExpContext>(_ctx, parentState);
  SysYParser::AddExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, SysYParser::RuleAddExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(315);
    mulExp(0);
    _ctx->stop = _input->LT(-1);
    setState(322);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAddExp);
        setState(317);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(318);
        _la = _input->LA(1);
        if (!(_la == SysYParser::T__20

        || _la == SysYParser::T__21)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(319);
        mulExp(0); 
      }
      setState(324);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RelExpContext ------------------------------------------------------------------

SysYParser::RelExpContext::RelExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::AddExpContext* SysYParser::RelExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}

SysYParser::RelExpContext* SysYParser::RelExpContext::relExp() {
  return getRuleContext<SysYParser::RelExpContext>(0);
}


size_t SysYParser::RelExpContext::getRuleIndex() const {
  return SysYParser::RuleRelExp;
}


std::any SysYParser::RelExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitRelExp(this);
  else
    return visitor->visitChildren(this);
}


SysYParser::RelExpContext* SysYParser::relExp() {
   return relExp(0);
}

SysYParser::RelExpContext* SysYParser::relExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::RelExpContext *_localctx = _tracker.createInstance<RelExpContext>(_ctx, parentState);
  SysYParser::RelExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, SysYParser::RuleRelExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(326);
    addExp(0);
    _ctx->stop = _input->LT(-1);
    setState(333);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<RelExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleRelExp);
        setState(328);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(329);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 2013265920) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(330);
        addExp(0); 
      }
      setState(335);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EqExpContext ------------------------------------------------------------------

SysYParser::EqExpContext::EqExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::RelExpContext* SysYParser::EqExpContext::relExp() {
  return getRuleContext<SysYParser::RelExpContext>(0);
}

SysYParser::EqExpContext* SysYParser::EqExpContext::eqExp() {
  return getRuleContext<SysYParser::EqExpContext>(0);
}


size_t SysYParser::EqExpContext::getRuleIndex() const {
  return SysYParser::RuleEqExp;
}


std::any SysYParser::EqExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitEqExp(this);
  else
    return visitor->visitChildren(this);
}


SysYParser::EqExpContext* SysYParser::eqExp() {
   return eqExp(0);
}

SysYParser::EqExpContext* SysYParser::eqExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::EqExpContext *_localctx = _tracker.createInstance<EqExpContext>(_ctx, parentState);
  SysYParser::EqExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, SysYParser::RuleEqExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(337);
    relExp(0);
    _ctx->stop = _input->LT(-1);
    setState(344);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<EqExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleEqExp);
        setState(339);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(340);
        _la = _input->LA(1);
        if (!(_la == SysYParser::T__30

        || _la == SysYParser::T__31)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(341);
        relExp(0); 
      }
      setState(346);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LAndExpContext ------------------------------------------------------------------

SysYParser::LAndExpContext::LAndExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::EqExpContext* SysYParser::LAndExpContext::eqExp() {
  return getRuleContext<SysYParser::EqExpContext>(0);
}

SysYParser::LAndExpContext* SysYParser::LAndExpContext::lAndExp() {
  return getRuleContext<SysYParser::LAndExpContext>(0);
}


size_t SysYParser::LAndExpContext::getRuleIndex() const {
  return SysYParser::RuleLAndExp;
}


std::any SysYParser::LAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLAndExp(this);
  else
    return visitor->visitChildren(this);
}


SysYParser::LAndExpContext* SysYParser::lAndExp() {
   return lAndExp(0);
}

SysYParser::LAndExpContext* SysYParser::lAndExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::LAndExpContext *_localctx = _tracker.createInstance<LAndExpContext>(_ctx, parentState);
  SysYParser::LAndExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, SysYParser::RuleLAndExp, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(348);
    eqExp(0);
    _ctx->stop = _input->LT(-1);
    setState(355);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LAndExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLAndExp);
        setState(350);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(351);
        match(SysYParser::T__32);
        setState(352);
        eqExp(0); 
      }
      setState(357);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LOrExpContext ------------------------------------------------------------------

SysYParser::LOrExpContext::LOrExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::LAndExpContext* SysYParser::LOrExpContext::lAndExp() {
  return getRuleContext<SysYParser::LAndExpContext>(0);
}

SysYParser::LOrExpContext* SysYParser::LOrExpContext::lOrExp() {
  return getRuleContext<SysYParser::LOrExpContext>(0);
}


size_t SysYParser::LOrExpContext::getRuleIndex() const {
  return SysYParser::RuleLOrExp;
}


std::any SysYParser::LOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLOrExp(this);
  else
    return visitor->visitChildren(this);
}


SysYParser::LOrExpContext* SysYParser::lOrExp() {
   return lOrExp(0);
}

SysYParser::LOrExpContext* SysYParser::lOrExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::LOrExpContext *_localctx = _tracker.createInstance<LOrExpContext>(_ctx, parentState);
  SysYParser::LOrExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, SysYParser::RuleLOrExp, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(359);
    lAndExp(0);
    _ctx->stop = _input->LT(-1);
    setState(366);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LOrExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLOrExp);
        setState(361);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(362);
        match(SysYParser::T__33);
        setState(363);
        lAndExp(0); 
      }
      setState(368);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConstExpContext ------------------------------------------------------------------

SysYParser::ConstExpContext::ConstExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::AddExpContext* SysYParser::ConstExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}


size_t SysYParser::ConstExpContext::getRuleIndex() const {
  return SysYParser::RuleConstExp;
}


std::any SysYParser::ConstExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitConstExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ConstExpContext* SysYParser::constExp() {
  ConstExpContext *_localctx = _tracker.createInstance<ConstExpContext>(_ctx, getState());
  enterRule(_localctx, 62, SysYParser::RuleConstExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(369);
    addExp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool SysYParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 25: return mulExpSempred(antlrcpp::downCast<MulExpContext *>(context), predicateIndex);
    case 26: return addExpSempred(antlrcpp::downCast<AddExpContext *>(context), predicateIndex);
    case 27: return relExpSempred(antlrcpp::downCast<RelExpContext *>(context), predicateIndex);
    case 28: return eqExpSempred(antlrcpp::downCast<EqExpContext *>(context), predicateIndex);
    case 29: return lAndExpSempred(antlrcpp::downCast<LAndExpContext *>(context), predicateIndex);
    case 30: return lOrExpSempred(antlrcpp::downCast<LOrExpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SysYParser::mulExpSempred(MulExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::addExpSempred(AddExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::relExpSempred(RelExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::eqExpSempred(EqExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::lAndExpSempred(LAndExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::lOrExpSempred(LOrExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void SysYParser::initialize() {
  ::antlr4::internal::call_once(sysyParserOnceFlag, sysyParserInitialize);
}
