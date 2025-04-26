
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
      "compileUnit", "decl", "constDecl", "basicType", "constDef", "constInitVal", 
      "varDecl", "varDef", "initVal", "funcDef", "funcType", "funcFParams", 
      "funcFParam", "block", "blockItem", "stmt", "exp", "cond", "lVal", 
      "primaryExp", "number", "unaryExp", "unaryOp", "funcRParams", "mulExp", 
      "addExp", "relExp", "eqExp", "lAndExp", "lOrExp", "constExp"
    },
    std::vector<std::string>{
      "", "'const'", "','", "';'", "'int'", "'float'", "'['", "']'", "'='", 
      "'{'", "'}'", "'('", "')'", "'void'", "'if'", "'else'", "'while'", 
      "'break'", "'continue'", "'return'", "'+'", "'-'", "'!'", "'*'", "'/'", 
      "'%'", "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", "'&&'", "'||'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "Ident", "IntConst", "DecimalConst", "OctalConst", "HexadecimalConst", 
      "HexadecimalPrefix", "NonzeroDigit", "Digit", "OctalDigit", "HexadecimalDigit", 
      "FloatConst", "ExponentPart", "WS", "COMMENT", "BLOCK_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,48,365,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,1,0,1,0,5,0,65,8,0,10,0,12,0,68,9,0,1,0,1,0,1,
  	1,1,1,3,1,74,8,1,1,2,1,2,1,2,1,2,1,2,5,2,81,8,2,10,2,12,2,84,9,2,1,2,
  	1,2,1,3,1,3,1,4,1,4,1,4,1,4,1,4,5,4,95,8,4,10,4,12,4,98,9,4,1,4,1,4,1,
  	4,1,5,1,5,1,5,1,5,1,5,5,5,108,8,5,10,5,12,5,111,9,5,3,5,113,8,5,1,5,3,
  	5,116,8,5,1,6,1,6,1,6,1,6,5,6,122,8,6,10,6,12,6,125,9,6,1,6,1,6,1,7,1,
  	7,1,7,1,7,1,7,5,7,134,8,7,10,7,12,7,137,9,7,1,7,1,7,1,7,1,7,1,7,5,7,144,
  	8,7,10,7,12,7,147,9,7,1,7,1,7,3,7,151,8,7,1,8,1,8,1,8,1,8,1,8,5,8,158,
  	8,8,10,8,12,8,161,9,8,3,8,163,8,8,1,8,3,8,166,8,8,1,9,1,9,1,9,1,9,3,9,
  	172,8,9,1,9,1,9,1,9,1,10,1,10,1,11,1,11,1,11,5,11,182,8,11,10,11,12,11,
  	185,9,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,195,8,12,10,12,
  	12,12,198,9,12,3,12,200,8,12,1,13,1,13,5,13,204,8,13,10,13,12,13,207,
  	9,13,1,13,1,13,1,14,1,14,3,14,213,8,14,1,15,1,15,1,15,1,15,1,15,1,15,
  	3,15,221,8,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,232,8,
  	15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,246,
  	8,15,1,15,3,15,249,8,15,1,16,1,16,1,17,1,17,1,18,1,18,1,18,1,18,1,18,
  	5,18,260,8,18,10,18,12,18,263,9,18,1,19,1,19,1,19,1,19,1,19,1,19,3,19,
  	271,8,19,1,20,1,20,1,21,1,21,1,21,1,21,3,21,279,8,21,1,21,1,21,1,21,1,
  	21,3,21,285,8,21,1,22,1,22,1,23,1,23,1,23,5,23,292,8,23,10,23,12,23,295,
  	9,23,1,24,1,24,1,24,1,24,1,24,1,24,5,24,303,8,24,10,24,12,24,306,9,24,
  	1,25,1,25,1,25,1,25,1,25,1,25,5,25,314,8,25,10,25,12,25,317,9,25,1,26,
  	1,26,1,26,1,26,1,26,1,26,5,26,325,8,26,10,26,12,26,328,9,26,1,27,1,27,
  	1,27,1,27,1,27,1,27,5,27,336,8,27,10,27,12,27,339,9,27,1,28,1,28,1,28,
  	1,28,1,28,1,28,5,28,347,8,28,10,28,12,28,350,9,28,1,29,1,29,1,29,1,29,
  	1,29,1,29,5,29,358,8,29,10,29,12,29,361,9,29,1,30,1,30,1,30,0,6,48,50,
  	52,54,56,58,31,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,
  	40,42,44,46,48,50,52,54,56,58,60,0,8,1,0,4,5,2,0,4,5,13,13,2,0,35,35,
  	44,44,1,0,20,22,1,0,23,25,1,0,20,21,1,0,26,29,1,0,30,31,377,0,66,1,0,
  	0,0,2,73,1,0,0,0,4,75,1,0,0,0,6,87,1,0,0,0,8,89,1,0,0,0,10,115,1,0,0,
  	0,12,117,1,0,0,0,14,150,1,0,0,0,16,165,1,0,0,0,18,167,1,0,0,0,20,176,
  	1,0,0,0,22,178,1,0,0,0,24,186,1,0,0,0,26,201,1,0,0,0,28,212,1,0,0,0,30,
  	248,1,0,0,0,32,250,1,0,0,0,34,252,1,0,0,0,36,254,1,0,0,0,38,270,1,0,0,
  	0,40,272,1,0,0,0,42,284,1,0,0,0,44,286,1,0,0,0,46,288,1,0,0,0,48,296,
  	1,0,0,0,50,307,1,0,0,0,52,318,1,0,0,0,54,329,1,0,0,0,56,340,1,0,0,0,58,
  	351,1,0,0,0,60,362,1,0,0,0,62,65,3,2,1,0,63,65,3,18,9,0,64,62,1,0,0,0,
  	64,63,1,0,0,0,65,68,1,0,0,0,66,64,1,0,0,0,66,67,1,0,0,0,67,69,1,0,0,0,
  	68,66,1,0,0,0,69,70,5,0,0,1,70,1,1,0,0,0,71,74,3,4,2,0,72,74,3,12,6,0,
  	73,71,1,0,0,0,73,72,1,0,0,0,74,3,1,0,0,0,75,76,5,1,0,0,76,77,3,6,3,0,
  	77,82,3,8,4,0,78,79,5,2,0,0,79,81,3,8,4,0,80,78,1,0,0,0,81,84,1,0,0,0,
  	82,80,1,0,0,0,82,83,1,0,0,0,83,85,1,0,0,0,84,82,1,0,0,0,85,86,5,3,0,0,
  	86,5,1,0,0,0,87,88,7,0,0,0,88,7,1,0,0,0,89,96,5,34,0,0,90,91,5,6,0,0,
  	91,92,3,60,30,0,92,93,5,7,0,0,93,95,1,0,0,0,94,90,1,0,0,0,95,98,1,0,0,
  	0,96,94,1,0,0,0,96,97,1,0,0,0,97,99,1,0,0,0,98,96,1,0,0,0,99,100,5,8,
  	0,0,100,101,3,10,5,0,101,9,1,0,0,0,102,116,3,60,30,0,103,112,5,9,0,0,
  	104,109,3,10,5,0,105,106,5,2,0,0,106,108,3,10,5,0,107,105,1,0,0,0,108,
  	111,1,0,0,0,109,107,1,0,0,0,109,110,1,0,0,0,110,113,1,0,0,0,111,109,1,
  	0,0,0,112,104,1,0,0,0,112,113,1,0,0,0,113,114,1,0,0,0,114,116,5,10,0,
  	0,115,102,1,0,0,0,115,103,1,0,0,0,116,11,1,0,0,0,117,118,3,6,3,0,118,
  	123,3,14,7,0,119,120,5,2,0,0,120,122,3,14,7,0,121,119,1,0,0,0,122,125,
  	1,0,0,0,123,121,1,0,0,0,123,124,1,0,0,0,124,126,1,0,0,0,125,123,1,0,0,
  	0,126,127,5,3,0,0,127,13,1,0,0,0,128,135,5,34,0,0,129,130,5,6,0,0,130,
  	131,3,60,30,0,131,132,5,7,0,0,132,134,1,0,0,0,133,129,1,0,0,0,134,137,
  	1,0,0,0,135,133,1,0,0,0,135,136,1,0,0,0,136,151,1,0,0,0,137,135,1,0,0,
  	0,138,145,5,34,0,0,139,140,5,6,0,0,140,141,3,60,30,0,141,142,5,7,0,0,
  	142,144,1,0,0,0,143,139,1,0,0,0,144,147,1,0,0,0,145,143,1,0,0,0,145,146,
  	1,0,0,0,146,148,1,0,0,0,147,145,1,0,0,0,148,149,5,8,0,0,149,151,3,16,
  	8,0,150,128,1,0,0,0,150,138,1,0,0,0,151,15,1,0,0,0,152,166,3,32,16,0,
  	153,162,5,9,0,0,154,159,3,16,8,0,155,156,5,2,0,0,156,158,3,16,8,0,157,
  	155,1,0,0,0,158,161,1,0,0,0,159,157,1,0,0,0,159,160,1,0,0,0,160,163,1,
  	0,0,0,161,159,1,0,0,0,162,154,1,0,0,0,162,163,1,0,0,0,163,164,1,0,0,0,
  	164,166,5,10,0,0,165,152,1,0,0,0,165,153,1,0,0,0,166,17,1,0,0,0,167,168,
  	3,20,10,0,168,169,5,34,0,0,169,171,5,11,0,0,170,172,3,22,11,0,171,170,
  	1,0,0,0,171,172,1,0,0,0,172,173,1,0,0,0,173,174,5,12,0,0,174,175,3,26,
  	13,0,175,19,1,0,0,0,176,177,7,1,0,0,177,21,1,0,0,0,178,183,3,24,12,0,
  	179,180,5,2,0,0,180,182,3,24,12,0,181,179,1,0,0,0,182,185,1,0,0,0,183,
  	181,1,0,0,0,183,184,1,0,0,0,184,23,1,0,0,0,185,183,1,0,0,0,186,187,3,
  	6,3,0,187,199,5,34,0,0,188,189,5,6,0,0,189,196,5,7,0,0,190,191,5,6,0,
  	0,191,192,3,32,16,0,192,193,5,7,0,0,193,195,1,0,0,0,194,190,1,0,0,0,195,
  	198,1,0,0,0,196,194,1,0,0,0,196,197,1,0,0,0,197,200,1,0,0,0,198,196,1,
  	0,0,0,199,188,1,0,0,0,199,200,1,0,0,0,200,25,1,0,0,0,201,205,5,9,0,0,
  	202,204,3,28,14,0,203,202,1,0,0,0,204,207,1,0,0,0,205,203,1,0,0,0,205,
  	206,1,0,0,0,206,208,1,0,0,0,207,205,1,0,0,0,208,209,5,10,0,0,209,27,1,
  	0,0,0,210,213,3,2,1,0,211,213,3,30,15,0,212,210,1,0,0,0,212,211,1,0,0,
  	0,213,29,1,0,0,0,214,215,3,36,18,0,215,216,5,8,0,0,216,217,3,32,16,0,
  	217,218,5,3,0,0,218,249,1,0,0,0,219,221,3,32,16,0,220,219,1,0,0,0,220,
  	221,1,0,0,0,221,222,1,0,0,0,222,249,5,3,0,0,223,249,3,26,13,0,224,225,
  	5,14,0,0,225,226,5,11,0,0,226,227,3,34,17,0,227,228,5,12,0,0,228,231,
  	3,30,15,0,229,230,5,15,0,0,230,232,3,30,15,0,231,229,1,0,0,0,231,232,
  	1,0,0,0,232,249,1,0,0,0,233,234,5,16,0,0,234,235,5,11,0,0,235,236,3,34,
  	17,0,236,237,5,12,0,0,237,238,3,30,15,0,238,249,1,0,0,0,239,240,5,17,
  	0,0,240,249,5,3,0,0,241,242,5,18,0,0,242,249,5,3,0,0,243,245,5,19,0,0,
  	244,246,3,32,16,0,245,244,1,0,0,0,245,246,1,0,0,0,246,247,1,0,0,0,247,
  	249,5,3,0,0,248,214,1,0,0,0,248,220,1,0,0,0,248,223,1,0,0,0,248,224,1,
  	0,0,0,248,233,1,0,0,0,248,239,1,0,0,0,248,241,1,0,0,0,248,243,1,0,0,0,
  	249,31,1,0,0,0,250,251,3,50,25,0,251,33,1,0,0,0,252,253,3,58,29,0,253,
  	35,1,0,0,0,254,261,5,34,0,0,255,256,5,6,0,0,256,257,3,32,16,0,257,258,
  	5,7,0,0,258,260,1,0,0,0,259,255,1,0,0,0,260,263,1,0,0,0,261,259,1,0,0,
  	0,261,262,1,0,0,0,262,37,1,0,0,0,263,261,1,0,0,0,264,265,5,11,0,0,265,
  	266,3,32,16,0,266,267,5,12,0,0,267,271,1,0,0,0,268,271,3,36,18,0,269,
  	271,3,40,20,0,270,264,1,0,0,0,270,268,1,0,0,0,270,269,1,0,0,0,271,39,
  	1,0,0,0,272,273,7,2,0,0,273,41,1,0,0,0,274,285,3,38,19,0,275,276,5,34,
  	0,0,276,278,5,11,0,0,277,279,3,46,23,0,278,277,1,0,0,0,278,279,1,0,0,
  	0,279,280,1,0,0,0,280,285,5,12,0,0,281,282,3,44,22,0,282,283,3,42,21,
  	0,283,285,1,0,0,0,284,274,1,0,0,0,284,275,1,0,0,0,284,281,1,0,0,0,285,
  	43,1,0,0,0,286,287,7,3,0,0,287,45,1,0,0,0,288,293,3,32,16,0,289,290,5,
  	2,0,0,290,292,3,32,16,0,291,289,1,0,0,0,292,295,1,0,0,0,293,291,1,0,0,
  	0,293,294,1,0,0,0,294,47,1,0,0,0,295,293,1,0,0,0,296,297,6,24,-1,0,297,
  	298,3,42,21,0,298,304,1,0,0,0,299,300,10,1,0,0,300,301,7,4,0,0,301,303,
  	3,42,21,0,302,299,1,0,0,0,303,306,1,0,0,0,304,302,1,0,0,0,304,305,1,0,
  	0,0,305,49,1,0,0,0,306,304,1,0,0,0,307,308,6,25,-1,0,308,309,3,48,24,
  	0,309,315,1,0,0,0,310,311,10,1,0,0,311,312,7,5,0,0,312,314,3,48,24,0,
  	313,310,1,0,0,0,314,317,1,0,0,0,315,313,1,0,0,0,315,316,1,0,0,0,316,51,
  	1,0,0,0,317,315,1,0,0,0,318,319,6,26,-1,0,319,320,3,50,25,0,320,326,1,
  	0,0,0,321,322,10,1,0,0,322,323,7,6,0,0,323,325,3,50,25,0,324,321,1,0,
  	0,0,325,328,1,0,0,0,326,324,1,0,0,0,326,327,1,0,0,0,327,53,1,0,0,0,328,
  	326,1,0,0,0,329,330,6,27,-1,0,330,331,3,52,26,0,331,337,1,0,0,0,332,333,
  	10,1,0,0,333,334,7,7,0,0,334,336,3,52,26,0,335,332,1,0,0,0,336,339,1,
  	0,0,0,337,335,1,0,0,0,337,338,1,0,0,0,338,55,1,0,0,0,339,337,1,0,0,0,
  	340,341,6,28,-1,0,341,342,3,54,27,0,342,348,1,0,0,0,343,344,10,1,0,0,
  	344,345,5,32,0,0,345,347,3,54,27,0,346,343,1,0,0,0,347,350,1,0,0,0,348,
  	346,1,0,0,0,348,349,1,0,0,0,349,57,1,0,0,0,350,348,1,0,0,0,351,352,6,
  	29,-1,0,352,353,3,56,28,0,353,359,1,0,0,0,354,355,10,1,0,0,355,356,5,
  	33,0,0,356,358,3,56,28,0,357,354,1,0,0,0,358,361,1,0,0,0,359,357,1,0,
  	0,0,359,360,1,0,0,0,360,59,1,0,0,0,361,359,1,0,0,0,362,363,3,50,25,0,
  	363,61,1,0,0,0,36,64,66,73,82,96,109,112,115,123,135,145,150,159,162,
  	165,171,183,196,199,205,212,220,231,245,248,261,270,278,284,293,304,315,
  	326,337,348,359
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
    setState(66);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8242) != 0)) {
      setState(64);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(62);
        decl();
        break;
      }

      case 2: {
        setState(63);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(68);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(69);
    match(SysYParser::EOF);
   
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
  enterRule(_localctx, 2, SysYParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(73);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(71);
        constDecl();
        break;
      }

      case SysYParser::T__3:
      case SysYParser::T__4: {
        enterOuterAlt(_localctx, 2);
        setState(72);
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
  enterRule(_localctx, 4, SysYParser::RuleConstDecl);
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
    setState(75);
    match(SysYParser::T__0);
    setState(76);
    basicType();
    setState(77);
    constDef();
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__1) {
      setState(78);
      match(SysYParser::T__1);
      setState(79);
      constDef();
      setState(84);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(85);
    match(SysYParser::T__2);
   
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
  enterRule(_localctx, 6, SysYParser::RuleBasicType);
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
    setState(87);
    _la = _input->LA(1);
    if (!(_la == SysYParser::T__3

    || _la == SysYParser::T__4)) {
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
  enterRule(_localctx, 8, SysYParser::RuleConstDef);
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
    setState(89);
    match(SysYParser::Ident);
    setState(96);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__5) {
      setState(90);
      match(SysYParser::T__5);
      setState(91);
      constExp();
      setState(92);
      match(SysYParser::T__6);
      setState(98);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(99);
    match(SysYParser::T__7);
    setState(100);
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
  enterRule(_localctx, 10, SysYParser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(115);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__10:
      case SysYParser::T__19:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::Ident:
      case SysYParser::IntConst:
      case SysYParser::FloatConst: {
        _localctx = _tracker.createInstance<SysYParser::SingleConstantInitContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(102);
        constExp();
        break;
      }

      case SysYParser::T__8: {
        _localctx = _tracker.createInstance<SysYParser::ArrayConstantInitContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(103);
        match(SysYParser::T__8);
        setState(112);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 17643732994560) != 0)) {
          setState(104);
          constInitVal();
          setState(109);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYParser::T__1) {
            setState(105);
            match(SysYParser::T__1);
            setState(106);
            constInitVal();
            setState(111);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(114);
        match(SysYParser::T__9);
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
  enterRule(_localctx, 12, SysYParser::RuleVarDecl);
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
    setState(117);
    basicType();
    setState(118);
    varDef();
    setState(123);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__1) {
      setState(119);
      match(SysYParser::T__1);
      setState(120);
      varDef();
      setState(125);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(126);
    match(SysYParser::T__2);
   
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
  enterRule(_localctx, 14, SysYParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(150);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::SimpleVarDefContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(128);
      match(SysYParser::Ident);
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__5) {
        setState(129);
        match(SysYParser::T__5);
        setState(130);
        constExp();
        setState(131);
        match(SysYParser::T__6);
        setState(137);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::InitializedVarDefContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(138);
      match(SysYParser::Ident);
      setState(145);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__5) {
        setState(139);
        match(SysYParser::T__5);
        setState(140);
        constExp();
        setState(141);
        match(SysYParser::T__6);
        setState(147);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(148);
      match(SysYParser::T__7);
      setState(149);
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
  enterRule(_localctx, 16, SysYParser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(165);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__10:
      case SysYParser::T__19:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::Ident:
      case SysYParser::IntConst:
      case SysYParser::FloatConst: {
        _localctx = _tracker.createInstance<SysYParser::SingleVarInitContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(152);
        exp();
        break;
      }

      case SysYParser::T__8: {
        _localctx = _tracker.createInstance<SysYParser::ArrayVarInitContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(153);
        match(SysYParser::T__8);
        setState(162);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 17643732994560) != 0)) {
          setState(154);
          initVal();
          setState(159);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYParser::T__1) {
            setState(155);
            match(SysYParser::T__1);
            setState(156);
            initVal();
            setState(161);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(164);
        match(SysYParser::T__9);
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
  enterRule(_localctx, 18, SysYParser::RuleFuncDef);
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
    setState(167);
    funcType();
    setState(168);
    match(SysYParser::Ident);
    setState(169);
    match(SysYParser::T__10);
    setState(171);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::T__3

    || _la == SysYParser::T__4) {
      setState(170);
      funcFParams();
    }
    setState(173);
    match(SysYParser::T__11);
    setState(174);
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
  enterRule(_localctx, 20, SysYParser::RuleFuncType);
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
    setState(176);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8240) != 0))) {
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
  enterRule(_localctx, 22, SysYParser::RuleFuncFParams);
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
    setState(178);
    funcFParam();
    setState(183);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__1) {
      setState(179);
      match(SysYParser::T__1);
      setState(180);
      funcFParam();
      setState(185);
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
  enterRule(_localctx, 24, SysYParser::RuleFuncFParam);
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
    setState(186);
    basicType();
    setState(187);
    match(SysYParser::Ident);
    setState(199);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::T__5) {
      setState(188);
      match(SysYParser::T__5);
      setState(189);
      match(SysYParser::T__6);
      setState(196);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__5) {
        setState(190);
        match(SysYParser::T__5);
        setState(191);
        exp();
        setState(192);
        match(SysYParser::T__6);
        setState(198);
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
  enterRule(_localctx, 26, SysYParser::RuleBlock);
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
    setState(201);
    match(SysYParser::T__8);
    setState(205);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17643733994042) != 0)) {
      setState(202);
      blockItem();
      setState(207);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(208);
    match(SysYParser::T__9);
   
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
  enterRule(_localctx, 28, SysYParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(212);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__0:
      case SysYParser::T__3:
      case SysYParser::T__4: {
        _localctx = _tracker.createInstance<SysYParser::DeclarationBlockItemContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(210);
        decl();
        break;
      }

      case SysYParser::T__2:
      case SysYParser::T__8:
      case SysYParser::T__10:
      case SysYParser::T__13:
      case SysYParser::T__15:
      case SysYParser::T__16:
      case SysYParser::T__17:
      case SysYParser::T__18:
      case SysYParser::T__19:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::Ident:
      case SysYParser::IntConst:
      case SysYParser::FloatConst: {
        _localctx = _tracker.createInstance<SysYParser::StatementBlockItemContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(211);
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
  enterRule(_localctx, 30, SysYParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(248);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::AssignmentStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(214);
      lVal();
      setState(215);
      match(SysYParser::T__7);
      setState(216);
      exp();
      setState(217);
      match(SysYParser::T__2);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(220);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 17643732994048) != 0)) {
        setState(219);
        exp();
      }
      setState(222);
      match(SysYParser::T__2);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::NestedBlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(223);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SysYParser::IfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(224);
      match(SysYParser::T__13);
      setState(225);
      match(SysYParser::T__10);
      setState(226);
      cond();
      setState(227);
      match(SysYParser::T__11);
      setState(228);
      stmt();
      setState(231);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(229);
        match(SysYParser::T__14);
        setState(230);
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
      setState(233);
      match(SysYParser::T__15);
      setState(234);
      match(SysYParser::T__10);
      setState(235);
      cond();
      setState(236);
      match(SysYParser::T__11);
      setState(237);
      stmt();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SysYParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(239);
      match(SysYParser::T__16);
      setState(240);
      match(SysYParser::T__2);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SysYParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(241);
      match(SysYParser::T__17);
      setState(242);
      match(SysYParser::T__2);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<SysYParser::ReturnStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(243);
      match(SysYParser::T__18);
      setState(245);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 17643732994048) != 0)) {
        setState(244);
        exp();
      }
      setState(247);
      match(SysYParser::T__2);
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
  enterRule(_localctx, 32, SysYParser::RuleExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(250);
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
  enterRule(_localctx, 34, SysYParser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
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
  enterRule(_localctx, 36, SysYParser::RuleLVal);

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
    setState(254);
    match(SysYParser::Ident);
    setState(261);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(255);
        match(SysYParser::T__5);
        setState(256);
        exp();
        setState(257);
        match(SysYParser::T__6); 
      }
      setState(263);
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
  enterRule(_localctx, 38, SysYParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(270);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__10: {
        _localctx = _tracker.createInstance<SysYParser::GroupedExpressionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(264);
        match(SysYParser::T__10);
        setState(265);
        exp();
        setState(266);
        match(SysYParser::T__11);
        break;
      }

      case SysYParser::Ident: {
        _localctx = _tracker.createInstance<SysYParser::LeftValueExpressionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(268);
        lVal();
        break;
      }

      case SysYParser::IntConst:
      case SysYParser::FloatConst: {
        _localctx = _tracker.createInstance<SysYParser::NumberExpressionContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(269);
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
  enterRule(_localctx, 40, SysYParser::RuleNumber);
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
    setState(272);
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
  enterRule(_localctx, 42, SysYParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(284);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::PrimaryUnaryExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(274);
      primaryExp();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::FunctionCallContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(275);
      match(SysYParser::Ident);
      setState(276);
      match(SysYParser::T__10);
      setState(278);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 17643732994048) != 0)) {
        setState(277);
        funcRParams();
      }
      setState(280);
      match(SysYParser::T__11);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::UnaryOperatorExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(281);
      unaryOp();
      setState(282);
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
  enterRule(_localctx, 44, SysYParser::RuleUnaryOp);
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
    setState(286);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7340032) != 0))) {
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
  enterRule(_localctx, 46, SysYParser::RuleFuncRParams);
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
    setState(288);
    exp();
    setState(293);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__1) {
      setState(289);
      match(SysYParser::T__1);
      setState(290);
      exp();
      setState(295);
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
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, SysYParser::RuleMulExp, precedence);

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
    setState(297);
    unaryExp();
    _ctx->stop = _input->LT(-1);
    setState(304);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MulExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMulExp);
        setState(299);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(300);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 58720256) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(301);
        unaryExp(); 
      }
      setState(306);
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
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, SysYParser::RuleAddExp, precedence);

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
    setState(308);
    mulExp(0);
    _ctx->stop = _input->LT(-1);
    setState(315);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAddExp);
        setState(310);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(311);
        _la = _input->LA(1);
        if (!(_la == SysYParser::T__19

        || _la == SysYParser::T__20)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(312);
        mulExp(0); 
      }
      setState(317);
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
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, SysYParser::RuleRelExp, precedence);

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
    setState(319);
    addExp(0);
    _ctx->stop = _input->LT(-1);
    setState(326);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<RelExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleRelExp);
        setState(321);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(322);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1006632960) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(323);
        addExp(0); 
      }
      setState(328);
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
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, SysYParser::RuleEqExp, precedence);

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
    setState(330);
    relExp(0);
    _ctx->stop = _input->LT(-1);
    setState(337);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<EqExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleEqExp);
        setState(332);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(333);
        _la = _input->LA(1);
        if (!(_la == SysYParser::T__29

        || _la == SysYParser::T__30)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(334);
        relExp(0); 
      }
      setState(339);
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
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, SysYParser::RuleLAndExp, precedence);

    

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
    setState(341);
    eqExp(0);
    _ctx->stop = _input->LT(-1);
    setState(348);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LAndExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLAndExp);
        setState(343);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(344);
        match(SysYParser::T__31);
        setState(345);
        eqExp(0); 
      }
      setState(350);
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
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, SysYParser::RuleLOrExp, precedence);

    

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
    setState(352);
    lAndExp(0);
    _ctx->stop = _input->LT(-1);
    setState(359);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LOrExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLOrExp);
        setState(354);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(355);
        match(SysYParser::T__32);
        setState(356);
        lAndExp(0); 
      }
      setState(361);
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
  enterRule(_localctx, 60, SysYParser::RuleConstExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(362);
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
    case 24: return mulExpSempred(antlrcpp::downCast<MulExpContext *>(context), predicateIndex);
    case 25: return addExpSempred(antlrcpp::downCast<AddExpContext *>(context), predicateIndex);
    case 26: return relExpSempred(antlrcpp::downCast<RelExpContext *>(context), predicateIndex);
    case 27: return eqExpSempred(antlrcpp::downCast<EqExpContext *>(context), predicateIndex);
    case 28: return lAndExpSempred(antlrcpp::downCast<LAndExpContext *>(context), predicateIndex);
    case 29: return lOrExpSempred(antlrcpp::downCast<LOrExpContext *>(context), predicateIndex);

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
