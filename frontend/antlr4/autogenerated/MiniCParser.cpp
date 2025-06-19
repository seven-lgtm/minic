
// Generated from /home/code/exp03-minic-basic/exp03-minic-basic/exp04-minic-expr/frontend/antlr4/MiniC.g4 by ANTLR 4.12.0


#include "MiniCVisitor.h"

#include "MiniCParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MiniCParserStaticData final {
  MiniCParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MiniCParserStaticData(const MiniCParserStaticData&) = delete;
  MiniCParserStaticData(MiniCParserStaticData&&) = delete;
  MiniCParserStaticData& operator=(const MiniCParserStaticData&) = delete;
  MiniCParserStaticData& operator=(MiniCParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag minicParserOnceFlag;
MiniCParserStaticData *minicParserStaticData = nullptr;

void minicParserInitialize() {
  assert(minicParserStaticData == nullptr);
  auto staticData = std::make_unique<MiniCParserStaticData>(
    std::vector<std::string>{
      "compileUnit", "funcDef", "returnType", "paramList", "param", "arrayParam", 
      "block", "blockItemList", "blockItem", "varDecl", "varDef", "arraySuffix", 
      "basicType", "statement", "forInit", "varDeclNoSemi", "assignNoSemi", 
      "expr", "logicalOrExp", "logicalAndExp", "relExp", "relOp", "addExp", 
      "addOp", "mulExp", "mulOp", "unaryExp", "primaryExp", "realParamList", 
      "lVal", "arrayIndexing"
    },
    std::vector<std::string>{
      "", "'('", "')'", "';'", "'{'", "'}'", "'['", "']'", "'='", "','", 
      "'+'", "'-'", "'%'", "'*'", "'/'", "'<'", "'>'", "'<='", "'>='", "'=='", 
      "'!='", "'++'", "'--'", "'&&'", "'||'", "'!'", "'return'", "'int'", 
      "'void'", "'if'", "'else'", "'break'", "'continue'", "'while'", "'for'"
    },
    std::vector<std::string>{
      "", "T_L_PAREN", "T_R_PAREN", "T_SEMICOLON", "T_L_BRACE", "T_R_BRACE", 
      "T_L_BRACKET", "T_R_BRACKET", "T_ASSIGN", "T_COMMA", "T_ADD", "T_SUB", 
      "T_MOD", "T_MUL", "T_DIV", "T_LT", "T_GT", "T_LE", "T_GE", "T_EQ", 
      "T_NE", "T_INC", "T_DEC", "T_AND", "T_OR", "T_NOT", "T_RETURN", "T_INT", 
      "T_VOID", "T_IF", "T_ELSE", "T_BREAK", "T_CONTINUE", "T_WHILE", "T_FOR", 
      "T_ID", "T_DECIMAL", "T_OCTAL", "T_HEX", "LINE_COMMENT", "BLOCK_COMMENT", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,41,331,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,1,0,1,0,5,0,65,8,0,10,0,12,0,68,9,0,1,0,1,0,1,
  	1,1,1,1,1,1,1,3,1,76,8,1,1,1,1,1,1,1,1,2,1,2,1,3,1,3,1,3,5,3,86,8,3,10,
  	3,12,3,89,9,3,1,4,1,4,1,4,3,4,94,8,4,1,5,1,5,3,5,98,8,5,1,5,4,5,101,8,
  	5,11,5,12,5,102,1,6,1,6,3,6,107,8,6,1,6,1,6,1,7,4,7,112,8,7,11,7,12,7,
  	113,1,8,1,8,3,8,118,8,8,1,9,1,9,1,9,1,9,5,9,124,8,9,10,9,12,9,127,9,9,
  	1,9,1,9,1,10,1,10,3,10,133,8,10,1,10,1,10,3,10,137,8,10,1,11,1,11,1,11,
  	1,11,4,11,143,8,11,11,11,12,11,144,1,12,1,12,1,13,1,13,3,13,151,8,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,161,8,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,3,13,171,8,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,189,8,13,1,13,
  	1,13,1,13,1,13,3,13,195,8,13,1,13,1,13,3,13,199,8,13,1,13,1,13,3,13,203,
  	8,13,1,14,1,14,3,14,207,8,14,1,15,1,15,1,15,1,15,5,15,213,8,15,10,15,
  	12,15,216,9,15,1,16,1,16,1,16,1,16,1,17,1,17,1,18,1,18,1,18,5,18,227,
  	8,18,10,18,12,18,230,9,18,1,19,1,19,1,19,5,19,235,8,19,10,19,12,19,238,
  	9,19,1,20,1,20,1,20,1,20,5,20,244,8,20,10,20,12,20,247,9,20,1,21,1,21,
  	1,22,1,22,1,22,1,22,5,22,255,8,22,10,22,12,22,258,9,22,1,23,1,23,1,24,
  	1,24,1,24,1,24,5,24,266,8,24,10,24,12,24,269,9,24,1,25,1,25,1,26,5,26,
  	274,8,26,10,26,12,26,277,9,26,1,26,1,26,1,26,5,26,282,8,26,10,26,12,26,
  	285,9,26,1,26,5,26,288,8,26,10,26,12,26,291,9,26,1,26,1,26,1,26,3,26,
  	296,8,26,1,26,3,26,299,8,26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,
  	27,309,8,27,1,28,1,28,1,28,5,28,314,8,28,10,28,12,28,317,9,28,1,29,1,
  	29,3,29,321,8,29,1,30,1,30,1,30,1,30,4,30,327,8,30,11,30,12,30,328,1,
  	30,0,0,31,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,
  	44,46,48,50,52,54,56,58,60,0,6,1,0,27,28,1,0,15,20,1,0,10,11,1,0,12,14,
  	3,0,11,11,21,22,25,25,1,0,21,22,348,0,66,1,0,0,0,2,71,1,0,0,0,4,80,1,
  	0,0,0,6,82,1,0,0,0,8,90,1,0,0,0,10,100,1,0,0,0,12,104,1,0,0,0,14,111,
  	1,0,0,0,16,117,1,0,0,0,18,119,1,0,0,0,20,130,1,0,0,0,22,142,1,0,0,0,24,
  	146,1,0,0,0,26,202,1,0,0,0,28,206,1,0,0,0,30,208,1,0,0,0,32,217,1,0,0,
  	0,34,221,1,0,0,0,36,223,1,0,0,0,38,231,1,0,0,0,40,239,1,0,0,0,42,248,
  	1,0,0,0,44,250,1,0,0,0,46,259,1,0,0,0,48,261,1,0,0,0,50,270,1,0,0,0,52,
  	298,1,0,0,0,54,308,1,0,0,0,56,310,1,0,0,0,58,318,1,0,0,0,60,326,1,0,0,
  	0,62,65,3,2,1,0,63,65,3,18,9,0,64,62,1,0,0,0,64,63,1,0,0,0,65,68,1,0,
  	0,0,66,64,1,0,0,0,66,67,1,0,0,0,67,69,1,0,0,0,68,66,1,0,0,0,69,70,5,0,
  	0,1,70,1,1,0,0,0,71,72,3,4,2,0,72,73,5,35,0,0,73,75,5,1,0,0,74,76,3,6,
  	3,0,75,74,1,0,0,0,75,76,1,0,0,0,76,77,1,0,0,0,77,78,5,2,0,0,78,79,3,12,
  	6,0,79,3,1,0,0,0,80,81,7,0,0,0,81,5,1,0,0,0,82,87,3,8,4,0,83,84,5,9,0,
  	0,84,86,3,8,4,0,85,83,1,0,0,0,86,89,1,0,0,0,87,85,1,0,0,0,87,88,1,0,0,
  	0,88,7,1,0,0,0,89,87,1,0,0,0,90,91,3,24,12,0,91,93,5,35,0,0,92,94,3,10,
  	5,0,93,92,1,0,0,0,93,94,1,0,0,0,94,9,1,0,0,0,95,97,5,6,0,0,96,98,3,34,
  	17,0,97,96,1,0,0,0,97,98,1,0,0,0,98,99,1,0,0,0,99,101,5,7,0,0,100,95,
  	1,0,0,0,101,102,1,0,0,0,102,100,1,0,0,0,102,103,1,0,0,0,103,11,1,0,0,
  	0,104,106,5,4,0,0,105,107,3,14,7,0,106,105,1,0,0,0,106,107,1,0,0,0,107,
  	108,1,0,0,0,108,109,5,5,0,0,109,13,1,0,0,0,110,112,3,16,8,0,111,110,1,
  	0,0,0,112,113,1,0,0,0,113,111,1,0,0,0,113,114,1,0,0,0,114,15,1,0,0,0,
  	115,118,3,26,13,0,116,118,3,18,9,0,117,115,1,0,0,0,117,116,1,0,0,0,118,
  	17,1,0,0,0,119,120,3,24,12,0,120,125,3,20,10,0,121,122,5,9,0,0,122,124,
  	3,20,10,0,123,121,1,0,0,0,124,127,1,0,0,0,125,123,1,0,0,0,125,126,1,0,
  	0,0,126,128,1,0,0,0,127,125,1,0,0,0,128,129,5,3,0,0,129,19,1,0,0,0,130,
  	132,5,35,0,0,131,133,3,22,11,0,132,131,1,0,0,0,132,133,1,0,0,0,133,136,
  	1,0,0,0,134,135,5,8,0,0,135,137,3,34,17,0,136,134,1,0,0,0,136,137,1,0,
  	0,0,137,21,1,0,0,0,138,139,5,6,0,0,139,140,3,34,17,0,140,141,5,7,0,0,
  	141,143,1,0,0,0,142,138,1,0,0,0,143,144,1,0,0,0,144,142,1,0,0,0,144,145,
  	1,0,0,0,145,23,1,0,0,0,146,147,5,27,0,0,147,25,1,0,0,0,148,150,5,26,0,
  	0,149,151,3,34,17,0,150,149,1,0,0,0,150,151,1,0,0,0,151,152,1,0,0,0,152,
  	203,5,3,0,0,153,154,3,58,29,0,154,155,5,8,0,0,155,156,3,34,17,0,156,157,
  	5,3,0,0,157,203,1,0,0,0,158,203,3,12,6,0,159,161,3,34,17,0,160,159,1,
  	0,0,0,160,161,1,0,0,0,161,162,1,0,0,0,162,203,5,3,0,0,163,164,5,29,0,
  	0,164,165,5,1,0,0,165,166,3,34,17,0,166,167,5,2,0,0,167,170,3,26,13,0,
  	168,169,5,30,0,0,169,171,3,26,13,0,170,168,1,0,0,0,170,171,1,0,0,0,171,
  	203,1,0,0,0,172,173,5,33,0,0,173,174,5,1,0,0,174,175,3,34,17,0,175,176,
  	5,2,0,0,176,177,3,26,13,0,177,203,1,0,0,0,178,179,5,31,0,0,179,203,5,
  	3,0,0,180,181,5,32,0,0,181,203,5,3,0,0,182,183,5,34,0,0,183,188,5,1,0,
  	0,184,185,3,28,14,0,185,186,5,3,0,0,186,189,1,0,0,0,187,189,5,3,0,0,188,
  	184,1,0,0,0,188,187,1,0,0,0,189,194,1,0,0,0,190,191,3,34,17,0,191,192,
  	5,3,0,0,192,195,1,0,0,0,193,195,5,3,0,0,194,190,1,0,0,0,194,193,1,0,0,
  	0,195,198,1,0,0,0,196,199,3,34,17,0,197,199,3,32,16,0,198,196,1,0,0,0,
  	198,197,1,0,0,0,198,199,1,0,0,0,199,200,1,0,0,0,200,201,5,2,0,0,201,203,
  	3,26,13,0,202,148,1,0,0,0,202,153,1,0,0,0,202,158,1,0,0,0,202,160,1,0,
  	0,0,202,163,1,0,0,0,202,172,1,0,0,0,202,178,1,0,0,0,202,180,1,0,0,0,202,
  	182,1,0,0,0,203,27,1,0,0,0,204,207,3,30,15,0,205,207,3,32,16,0,206,204,
  	1,0,0,0,206,205,1,0,0,0,207,29,1,0,0,0,208,209,3,24,12,0,209,214,3,20,
  	10,0,210,211,5,9,0,0,211,213,3,20,10,0,212,210,1,0,0,0,213,216,1,0,0,
  	0,214,212,1,0,0,0,214,215,1,0,0,0,215,31,1,0,0,0,216,214,1,0,0,0,217,
  	218,3,58,29,0,218,219,5,8,0,0,219,220,3,34,17,0,220,33,1,0,0,0,221,222,
  	3,36,18,0,222,35,1,0,0,0,223,228,3,38,19,0,224,225,5,24,0,0,225,227,3,
  	38,19,0,226,224,1,0,0,0,227,230,1,0,0,0,228,226,1,0,0,0,228,229,1,0,0,
  	0,229,37,1,0,0,0,230,228,1,0,0,0,231,236,3,40,20,0,232,233,5,23,0,0,233,
  	235,3,40,20,0,234,232,1,0,0,0,235,238,1,0,0,0,236,234,1,0,0,0,236,237,
  	1,0,0,0,237,39,1,0,0,0,238,236,1,0,0,0,239,245,3,44,22,0,240,241,3,42,
  	21,0,241,242,3,44,22,0,242,244,1,0,0,0,243,240,1,0,0,0,244,247,1,0,0,
  	0,245,243,1,0,0,0,245,246,1,0,0,0,246,41,1,0,0,0,247,245,1,0,0,0,248,
  	249,7,1,0,0,249,43,1,0,0,0,250,256,3,48,24,0,251,252,3,46,23,0,252,253,
  	3,48,24,0,253,255,1,0,0,0,254,251,1,0,0,0,255,258,1,0,0,0,256,254,1,0,
  	0,0,256,257,1,0,0,0,257,45,1,0,0,0,258,256,1,0,0,0,259,260,7,2,0,0,260,
  	47,1,0,0,0,261,267,3,52,26,0,262,263,3,50,25,0,263,264,3,52,26,0,264,
  	266,1,0,0,0,265,262,1,0,0,0,266,269,1,0,0,0,267,265,1,0,0,0,267,268,1,
  	0,0,0,268,49,1,0,0,0,269,267,1,0,0,0,270,271,7,3,0,0,271,51,1,0,0,0,272,
  	274,7,4,0,0,273,272,1,0,0,0,274,277,1,0,0,0,275,273,1,0,0,0,275,276,1,
  	0,0,0,276,278,1,0,0,0,277,275,1,0,0,0,278,299,3,54,27,0,279,283,3,54,
  	27,0,280,282,7,5,0,0,281,280,1,0,0,0,282,285,1,0,0,0,283,281,1,0,0,0,
  	283,284,1,0,0,0,284,299,1,0,0,0,285,283,1,0,0,0,286,288,7,4,0,0,287,286,
  	1,0,0,0,288,291,1,0,0,0,289,287,1,0,0,0,289,290,1,0,0,0,290,292,1,0,0,
  	0,291,289,1,0,0,0,292,293,5,35,0,0,293,295,5,1,0,0,294,296,3,56,28,0,
  	295,294,1,0,0,0,295,296,1,0,0,0,296,297,1,0,0,0,297,299,5,2,0,0,298,275,
  	1,0,0,0,298,279,1,0,0,0,298,289,1,0,0,0,299,53,1,0,0,0,300,301,5,1,0,
  	0,301,302,3,34,17,0,302,303,5,2,0,0,303,309,1,0,0,0,304,309,3,58,29,0,
  	305,309,5,36,0,0,306,309,5,37,0,0,307,309,5,38,0,0,308,300,1,0,0,0,308,
  	304,1,0,0,0,308,305,1,0,0,0,308,306,1,0,0,0,308,307,1,0,0,0,309,55,1,
  	0,0,0,310,315,3,34,17,0,311,312,5,9,0,0,312,314,3,34,17,0,313,311,1,0,
  	0,0,314,317,1,0,0,0,315,313,1,0,0,0,315,316,1,0,0,0,316,57,1,0,0,0,317,
  	315,1,0,0,0,318,320,5,35,0,0,319,321,3,60,30,0,320,319,1,0,0,0,320,321,
  	1,0,0,0,321,59,1,0,0,0,322,323,5,6,0,0,323,324,3,34,17,0,324,325,5,7,
  	0,0,325,327,1,0,0,0,326,322,1,0,0,0,327,328,1,0,0,0,328,326,1,0,0,0,328,
  	329,1,0,0,0,329,61,1,0,0,0,37,64,66,75,87,93,97,102,106,113,117,125,132,
  	136,144,150,160,170,188,194,198,202,206,214,228,236,245,256,267,275,283,
  	289,295,298,308,315,320,328
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  minicParserStaticData = staticData.release();
}

}

MiniCParser::MiniCParser(TokenStream *input) : MiniCParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MiniCParser::MiniCParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MiniCParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *minicParserStaticData->atn, minicParserStaticData->decisionToDFA, minicParserStaticData->sharedContextCache, options);
}

MiniCParser::~MiniCParser() {
  delete _interpreter;
}

const atn::ATN& MiniCParser::getATN() const {
  return *minicParserStaticData->atn;
}

std::string MiniCParser::getGrammarFileName() const {
  return "MiniC.g4";
}

const std::vector<std::string>& MiniCParser::getRuleNames() const {
  return minicParserStaticData->ruleNames;
}

const dfa::Vocabulary& MiniCParser::getVocabulary() const {
  return minicParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MiniCParser::getSerializedATN() const {
  return minicParserStaticData->serializedATN;
}


//----------------- CompileUnitContext ------------------------------------------------------------------

MiniCParser::CompileUnitContext::CompileUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::CompileUnitContext::EOF() {
  return getToken(MiniCParser::EOF, 0);
}

std::vector<MiniCParser::FuncDefContext *> MiniCParser::CompileUnitContext::funcDef() {
  return getRuleContexts<MiniCParser::FuncDefContext>();
}

MiniCParser::FuncDefContext* MiniCParser::CompileUnitContext::funcDef(size_t i) {
  return getRuleContext<MiniCParser::FuncDefContext>(i);
}

std::vector<MiniCParser::VarDeclContext *> MiniCParser::CompileUnitContext::varDecl() {
  return getRuleContexts<MiniCParser::VarDeclContext>();
}

MiniCParser::VarDeclContext* MiniCParser::CompileUnitContext::varDecl(size_t i) {
  return getRuleContext<MiniCParser::VarDeclContext>(i);
}


size_t MiniCParser::CompileUnitContext::getRuleIndex() const {
  return MiniCParser::RuleCompileUnit;
}


std::any MiniCParser::CompileUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitCompileUnit(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::CompileUnitContext* MiniCParser::compileUnit() {
  CompileUnitContext *_localctx = _tracker.createInstance<CompileUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, MiniCParser::RuleCompileUnit);
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
    while (_la == MiniCParser::T_INT

    || _la == MiniCParser::T_VOID) {
      setState(64);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(62);
        funcDef();
        break;
      }

      case 2: {
        setState(63);
        varDecl();
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
    match(MiniCParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

MiniCParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::ReturnTypeContext* MiniCParser::FuncDefContext::returnType() {
  return getRuleContext<MiniCParser::ReturnTypeContext>(0);
}

tree::TerminalNode* MiniCParser::FuncDefContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

tree::TerminalNode* MiniCParser::FuncDefContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

tree::TerminalNode* MiniCParser::FuncDefContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

MiniCParser::BlockContext* MiniCParser::FuncDefContext::block() {
  return getRuleContext<MiniCParser::BlockContext>(0);
}

MiniCParser::ParamListContext* MiniCParser::FuncDefContext::paramList() {
  return getRuleContext<MiniCParser::ParamListContext>(0);
}


size_t MiniCParser::FuncDefContext::getRuleIndex() const {
  return MiniCParser::RuleFuncDef;
}


std::any MiniCParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::FuncDefContext* MiniCParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 2, MiniCParser::RuleFuncDef);
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
    setState(71);
    returnType();
    setState(72);
    match(MiniCParser::T_ID);
    setState(73);
    match(MiniCParser::T_L_PAREN);
    setState(75);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T_INT) {
      setState(74);
      paramList();
    }
    setState(77);
    match(MiniCParser::T_R_PAREN);
    setState(78);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnTypeContext ------------------------------------------------------------------

MiniCParser::ReturnTypeContext::ReturnTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::ReturnTypeContext::T_INT() {
  return getToken(MiniCParser::T_INT, 0);
}

tree::TerminalNode* MiniCParser::ReturnTypeContext::T_VOID() {
  return getToken(MiniCParser::T_VOID, 0);
}


size_t MiniCParser::ReturnTypeContext::getRuleIndex() const {
  return MiniCParser::RuleReturnType;
}


std::any MiniCParser::ReturnTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitReturnType(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ReturnTypeContext* MiniCParser::returnType() {
  ReturnTypeContext *_localctx = _tracker.createInstance<ReturnTypeContext>(_ctx, getState());
  enterRule(_localctx, 4, MiniCParser::RuleReturnType);
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
    setState(80);
    _la = _input->LA(1);
    if (!(_la == MiniCParser::T_INT

    || _la == MiniCParser::T_VOID)) {
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

//----------------- ParamListContext ------------------------------------------------------------------

MiniCParser::ParamListContext::ParamListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::ParamContext *> MiniCParser::ParamListContext::param() {
  return getRuleContexts<MiniCParser::ParamContext>();
}

MiniCParser::ParamContext* MiniCParser::ParamListContext::param(size_t i) {
  return getRuleContext<MiniCParser::ParamContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::ParamListContext::T_COMMA() {
  return getTokens(MiniCParser::T_COMMA);
}

tree::TerminalNode* MiniCParser::ParamListContext::T_COMMA(size_t i) {
  return getToken(MiniCParser::T_COMMA, i);
}


size_t MiniCParser::ParamListContext::getRuleIndex() const {
  return MiniCParser::RuleParamList;
}


std::any MiniCParser::ParamListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitParamList(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ParamListContext* MiniCParser::paramList() {
  ParamListContext *_localctx = _tracker.createInstance<ParamListContext>(_ctx, getState());
  enterRule(_localctx, 6, MiniCParser::RuleParamList);
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
    param();
    setState(87);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_COMMA) {
      setState(83);
      match(MiniCParser::T_COMMA);
      setState(84);
      param();
      setState(89);
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

//----------------- ParamContext ------------------------------------------------------------------

MiniCParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::BasicTypeContext* MiniCParser::ParamContext::basicType() {
  return getRuleContext<MiniCParser::BasicTypeContext>(0);
}

tree::TerminalNode* MiniCParser::ParamContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

MiniCParser::ArrayParamContext* MiniCParser::ParamContext::arrayParam() {
  return getRuleContext<MiniCParser::ArrayParamContext>(0);
}


size_t MiniCParser::ParamContext::getRuleIndex() const {
  return MiniCParser::RuleParam;
}


std::any MiniCParser::ParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitParam(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ParamContext* MiniCParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 8, MiniCParser::RuleParam);
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
    setState(90);
    basicType();
    setState(91);
    match(MiniCParser::T_ID);
    setState(93);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T_L_BRACKET) {
      setState(92);
      arrayParam();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayParamContext ------------------------------------------------------------------

MiniCParser::ArrayParamContext::ArrayParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MiniCParser::ArrayParamContext::T_L_BRACKET() {
  return getTokens(MiniCParser::T_L_BRACKET);
}

tree::TerminalNode* MiniCParser::ArrayParamContext::T_L_BRACKET(size_t i) {
  return getToken(MiniCParser::T_L_BRACKET, i);
}

std::vector<tree::TerminalNode *> MiniCParser::ArrayParamContext::T_R_BRACKET() {
  return getTokens(MiniCParser::T_R_BRACKET);
}

tree::TerminalNode* MiniCParser::ArrayParamContext::T_R_BRACKET(size_t i) {
  return getToken(MiniCParser::T_R_BRACKET, i);
}

std::vector<MiniCParser::ExprContext *> MiniCParser::ArrayParamContext::expr() {
  return getRuleContexts<MiniCParser::ExprContext>();
}

MiniCParser::ExprContext* MiniCParser::ArrayParamContext::expr(size_t i) {
  return getRuleContext<MiniCParser::ExprContext>(i);
}


size_t MiniCParser::ArrayParamContext::getRuleIndex() const {
  return MiniCParser::RuleArrayParam;
}


std::any MiniCParser::ArrayParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitArrayParam(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ArrayParamContext* MiniCParser::arrayParam() {
  ArrayParamContext *_localctx = _tracker.createInstance<ArrayParamContext>(_ctx, getState());
  enterRule(_localctx, 10, MiniCParser::RuleArrayParam);
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
    setState(100); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(95);
      match(MiniCParser::T_L_BRACKET);
      setState(97);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515435923458) != 0)) {
        setState(96);
        expr();
      }
      setState(99);
      match(MiniCParser::T_R_BRACKET);
      setState(102); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == MiniCParser::T_L_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

MiniCParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::BlockContext::T_L_BRACE() {
  return getToken(MiniCParser::T_L_BRACE, 0);
}

tree::TerminalNode* MiniCParser::BlockContext::T_R_BRACE() {
  return getToken(MiniCParser::T_R_BRACE, 0);
}

MiniCParser::BlockItemListContext* MiniCParser::BlockContext::blockItemList() {
  return getRuleContext<MiniCParser::BlockItemListContext>(0);
}


size_t MiniCParser::BlockContext::getRuleIndex() const {
  return MiniCParser::RuleBlock;
}


std::any MiniCParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::BlockContext* MiniCParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 12, MiniCParser::RuleBlock);
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
    setState(104);
    match(MiniCParser::T_L_BRACE);
    setState(106);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 548386375706) != 0)) {
      setState(105);
      blockItemList();
    }
    setState(108);
    match(MiniCParser::T_R_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemListContext ------------------------------------------------------------------

MiniCParser::BlockItemListContext::BlockItemListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::BlockItemContext *> MiniCParser::BlockItemListContext::blockItem() {
  return getRuleContexts<MiniCParser::BlockItemContext>();
}

MiniCParser::BlockItemContext* MiniCParser::BlockItemListContext::blockItem(size_t i) {
  return getRuleContext<MiniCParser::BlockItemContext>(i);
}


size_t MiniCParser::BlockItemListContext::getRuleIndex() const {
  return MiniCParser::RuleBlockItemList;
}


std::any MiniCParser::BlockItemListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlockItemList(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::BlockItemListContext* MiniCParser::blockItemList() {
  BlockItemListContext *_localctx = _tracker.createInstance<BlockItemListContext>(_ctx, getState());
  enterRule(_localctx, 14, MiniCParser::RuleBlockItemList);
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
    setState(111); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(110);
      blockItem();
      setState(113); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 548386375706) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

MiniCParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::StatementContext* MiniCParser::BlockItemContext::statement() {
  return getRuleContext<MiniCParser::StatementContext>(0);
}

MiniCParser::VarDeclContext* MiniCParser::BlockItemContext::varDecl() {
  return getRuleContext<MiniCParser::VarDeclContext>(0);
}


size_t MiniCParser::BlockItemContext::getRuleIndex() const {
  return MiniCParser::RuleBlockItem;
}


std::any MiniCParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::BlockItemContext* MiniCParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 16, MiniCParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(117);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T_L_PAREN:
      case MiniCParser::T_SEMICOLON:
      case MiniCParser::T_L_BRACE:
      case MiniCParser::T_SUB:
      case MiniCParser::T_INC:
      case MiniCParser::T_DEC:
      case MiniCParser::T_NOT:
      case MiniCParser::T_RETURN:
      case MiniCParser::T_IF:
      case MiniCParser::T_BREAK:
      case MiniCParser::T_CONTINUE:
      case MiniCParser::T_WHILE:
      case MiniCParser::T_FOR:
      case MiniCParser::T_ID:
      case MiniCParser::T_DECIMAL:
      case MiniCParser::T_OCTAL:
      case MiniCParser::T_HEX: {
        enterOuterAlt(_localctx, 1);
        setState(115);
        statement();
        break;
      }

      case MiniCParser::T_INT: {
        enterOuterAlt(_localctx, 2);
        setState(116);
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

//----------------- VarDeclContext ------------------------------------------------------------------

MiniCParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::BasicTypeContext* MiniCParser::VarDeclContext::basicType() {
  return getRuleContext<MiniCParser::BasicTypeContext>(0);
}

std::vector<MiniCParser::VarDefContext *> MiniCParser::VarDeclContext::varDef() {
  return getRuleContexts<MiniCParser::VarDefContext>();
}

MiniCParser::VarDefContext* MiniCParser::VarDeclContext::varDef(size_t i) {
  return getRuleContext<MiniCParser::VarDefContext>(i);
}

tree::TerminalNode* MiniCParser::VarDeclContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> MiniCParser::VarDeclContext::T_COMMA() {
  return getTokens(MiniCParser::T_COMMA);
}

tree::TerminalNode* MiniCParser::VarDeclContext::T_COMMA(size_t i) {
  return getToken(MiniCParser::T_COMMA, i);
}


size_t MiniCParser::VarDeclContext::getRuleIndex() const {
  return MiniCParser::RuleVarDecl;
}


std::any MiniCParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::VarDeclContext* MiniCParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 18, MiniCParser::RuleVarDecl);
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
    setState(119);
    basicType();
    setState(120);
    varDef();
    setState(125);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_COMMA) {
      setState(121);
      match(MiniCParser::T_COMMA);
      setState(122);
      varDef();
      setState(127);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(128);
    match(MiniCParser::T_SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

MiniCParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::VarDefContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

MiniCParser::ArraySuffixContext* MiniCParser::VarDefContext::arraySuffix() {
  return getRuleContext<MiniCParser::ArraySuffixContext>(0);
}

tree::TerminalNode* MiniCParser::VarDefContext::T_ASSIGN() {
  return getToken(MiniCParser::T_ASSIGN, 0);
}

MiniCParser::ExprContext* MiniCParser::VarDefContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}


size_t MiniCParser::VarDefContext::getRuleIndex() const {
  return MiniCParser::RuleVarDef;
}


std::any MiniCParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::VarDefContext* MiniCParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 20, MiniCParser::RuleVarDef);
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
    setState(130);
    match(MiniCParser::T_ID);
    setState(132);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T_L_BRACKET) {
      setState(131);
      arraySuffix();
    }
    setState(136);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T_ASSIGN) {
      setState(134);
      match(MiniCParser::T_ASSIGN);
      setState(135);
      expr();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArraySuffixContext ------------------------------------------------------------------

MiniCParser::ArraySuffixContext::ArraySuffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MiniCParser::ArraySuffixContext::T_L_BRACKET() {
  return getTokens(MiniCParser::T_L_BRACKET);
}

tree::TerminalNode* MiniCParser::ArraySuffixContext::T_L_BRACKET(size_t i) {
  return getToken(MiniCParser::T_L_BRACKET, i);
}

std::vector<MiniCParser::ExprContext *> MiniCParser::ArraySuffixContext::expr() {
  return getRuleContexts<MiniCParser::ExprContext>();
}

MiniCParser::ExprContext* MiniCParser::ArraySuffixContext::expr(size_t i) {
  return getRuleContext<MiniCParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::ArraySuffixContext::T_R_BRACKET() {
  return getTokens(MiniCParser::T_R_BRACKET);
}

tree::TerminalNode* MiniCParser::ArraySuffixContext::T_R_BRACKET(size_t i) {
  return getToken(MiniCParser::T_R_BRACKET, i);
}


size_t MiniCParser::ArraySuffixContext::getRuleIndex() const {
  return MiniCParser::RuleArraySuffix;
}


std::any MiniCParser::ArraySuffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitArraySuffix(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ArraySuffixContext* MiniCParser::arraySuffix() {
  ArraySuffixContext *_localctx = _tracker.createInstance<ArraySuffixContext>(_ctx, getState());
  enterRule(_localctx, 22, MiniCParser::RuleArraySuffix);
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
    setState(142); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(138);
      match(MiniCParser::T_L_BRACKET);
      setState(139);
      expr();
      setState(140);
      match(MiniCParser::T_R_BRACKET);
      setState(144); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == MiniCParser::T_L_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicTypeContext ------------------------------------------------------------------

MiniCParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::BasicTypeContext::T_INT() {
  return getToken(MiniCParser::T_INT, 0);
}


size_t MiniCParser::BasicTypeContext::getRuleIndex() const {
  return MiniCParser::RuleBasicType;
}


std::any MiniCParser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::BasicTypeContext* MiniCParser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 24, MiniCParser::RuleBasicType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    match(MiniCParser::T_INT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

MiniCParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::StatementContext::getRuleIndex() const {
  return MiniCParser::RuleStatement;
}

void MiniCParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- WhileStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::WhileStatementContext::T_WHILE() {
  return getToken(MiniCParser::T_WHILE, 0);
}

tree::TerminalNode* MiniCParser::WhileStatementContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

MiniCParser::ExprContext* MiniCParser::WhileStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

tree::TerminalNode* MiniCParser::WhileStatementContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

MiniCParser::StatementContext* MiniCParser::WhileStatementContext::statement() {
  return getRuleContext<MiniCParser::StatementContext>(0);
}

MiniCParser::WhileStatementContext::WhileStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStatementContext ------------------------------------------------------------------

MiniCParser::BlockContext* MiniCParser::BlockStatementContext::block() {
  return getRuleContext<MiniCParser::BlockContext>(0);
}

MiniCParser::BlockStatementContext::BlockStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlockStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStatementContext ------------------------------------------------------------------

MiniCParser::LValContext* MiniCParser::AssignStatementContext::lVal() {
  return getRuleContext<MiniCParser::LValContext>(0);
}

tree::TerminalNode* MiniCParser::AssignStatementContext::T_ASSIGN() {
  return getToken(MiniCParser::T_ASSIGN, 0);
}

MiniCParser::ExprContext* MiniCParser::AssignStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

tree::TerminalNode* MiniCParser::AssignStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::AssignStatementContext::AssignStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::AssignStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitAssignStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::BreakStatementContext::T_BREAK() {
  return getToken(MiniCParser::T_BREAK, 0);
}

tree::TerminalNode* MiniCParser::BreakStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::BreakStatementContext::BreakStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ForStatementContext::T_FOR() {
  return getToken(MiniCParser::T_FOR, 0);
}

tree::TerminalNode* MiniCParser::ForStatementContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

tree::TerminalNode* MiniCParser::ForStatementContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

MiniCParser::StatementContext* MiniCParser::ForStatementContext::statement() {
  return getRuleContext<MiniCParser::StatementContext>(0);
}

MiniCParser::ForInitContext* MiniCParser::ForStatementContext::forInit() {
  return getRuleContext<MiniCParser::ForInitContext>(0);
}

std::vector<tree::TerminalNode *> MiniCParser::ForStatementContext::T_SEMICOLON() {
  return getTokens(MiniCParser::T_SEMICOLON);
}

tree::TerminalNode* MiniCParser::ForStatementContext::T_SEMICOLON(size_t i) {
  return getToken(MiniCParser::T_SEMICOLON, i);
}

std::vector<MiniCParser::ExprContext *> MiniCParser::ForStatementContext::expr() {
  return getRuleContexts<MiniCParser::ExprContext>();
}

MiniCParser::ExprContext* MiniCParser::ForStatementContext::expr(size_t i) {
  return getRuleContext<MiniCParser::ExprContext>(i);
}

MiniCParser::AssignNoSemiContext* MiniCParser::ForStatementContext::assignNoSemi() {
  return getRuleContext<MiniCParser::AssignNoSemiContext>(0);
}

MiniCParser::ForStatementContext::ForStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpressionStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ExpressionStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::ExprContext* MiniCParser::ExpressionStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

MiniCParser::ExpressionStatementContext::ExpressionStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ContinueStatementContext::T_CONTINUE() {
  return getToken(MiniCParser::T_CONTINUE, 0);
}

tree::TerminalNode* MiniCParser::ContinueStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::ContinueStatementContext::ContinueStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ReturnStatementContext::T_RETURN() {
  return getToken(MiniCParser::T_RETURN, 0);
}

tree::TerminalNode* MiniCParser::ReturnStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::ExprContext* MiniCParser::ReturnStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

MiniCParser::ReturnStatementContext::ReturnStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::IfStatementContext::T_IF() {
  return getToken(MiniCParser::T_IF, 0);
}

tree::TerminalNode* MiniCParser::IfStatementContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

MiniCParser::ExprContext* MiniCParser::IfStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

tree::TerminalNode* MiniCParser::IfStatementContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

std::vector<MiniCParser::StatementContext *> MiniCParser::IfStatementContext::statement() {
  return getRuleContexts<MiniCParser::StatementContext>();
}

MiniCParser::StatementContext* MiniCParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<MiniCParser::StatementContext>(i);
}

tree::TerminalNode* MiniCParser::IfStatementContext::T_ELSE() {
  return getToken(MiniCParser::T_ELSE, 0);
}

MiniCParser::IfStatementContext::IfStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::StatementContext* MiniCParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 26, MiniCParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(202);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MiniCParser::ReturnStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(148);
      match(MiniCParser::T_RETURN);
      setState(150);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515435923458) != 0)) {
        setState(149);
        expr();
      }
      setState(152);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MiniCParser::AssignStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(153);
      lVal();
      setState(154);
      match(MiniCParser::T_ASSIGN);
      setState(155);
      expr();
      setState(156);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MiniCParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(158);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MiniCParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(160);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515435923458) != 0)) {
        setState(159);
        expr();
      }
      setState(162);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MiniCParser::IfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(163);
      match(MiniCParser::T_IF);
      setState(164);
      match(MiniCParser::T_L_PAREN);
      setState(165);
      expr();
      setState(166);
      match(MiniCParser::T_R_PAREN);
      setState(167);
      statement();
      setState(170);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(168);
        match(MiniCParser::T_ELSE);
        setState(169);
        statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<MiniCParser::WhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(172);
      match(MiniCParser::T_WHILE);
      setState(173);
      match(MiniCParser::T_L_PAREN);
      setState(174);
      expr();
      setState(175);
      match(MiniCParser::T_R_PAREN);
      setState(176);
      statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<MiniCParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(178);
      match(MiniCParser::T_BREAK);
      setState(179);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<MiniCParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(180);
      match(MiniCParser::T_CONTINUE);
      setState(181);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<MiniCParser::ForStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(182);
      match(MiniCParser::T_FOR);
      setState(183);
      match(MiniCParser::T_L_PAREN);
      setState(188);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case MiniCParser::T_INT:
        case MiniCParser::T_ID: {
          setState(184);
          forInit();
          setState(185);
          match(MiniCParser::T_SEMICOLON);
          break;
        }

        case MiniCParser::T_SEMICOLON: {
          setState(187);
          match(MiniCParser::T_SEMICOLON);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(194);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case MiniCParser::T_L_PAREN:
        case MiniCParser::T_SUB:
        case MiniCParser::T_INC:
        case MiniCParser::T_DEC:
        case MiniCParser::T_NOT:
        case MiniCParser::T_ID:
        case MiniCParser::T_DECIMAL:
        case MiniCParser::T_OCTAL:
        case MiniCParser::T_HEX: {
          setState(190);
          expr();
          setState(191);
          match(MiniCParser::T_SEMICOLON);
          break;
        }

        case MiniCParser::T_SEMICOLON: {
          setState(193);
          match(MiniCParser::T_SEMICOLON);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(198);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
      case 1: {
        setState(196);
        expr();
        break;
      }

      case 2: {
        setState(197);
        assignNoSemi();
        break;
      }

      default:
        break;
      }
      setState(200);
      match(MiniCParser::T_R_PAREN);
      setState(201);
      statement();
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

//----------------- ForInitContext ------------------------------------------------------------------

MiniCParser::ForInitContext::ForInitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::VarDeclNoSemiContext* MiniCParser::ForInitContext::varDeclNoSemi() {
  return getRuleContext<MiniCParser::VarDeclNoSemiContext>(0);
}

MiniCParser::AssignNoSemiContext* MiniCParser::ForInitContext::assignNoSemi() {
  return getRuleContext<MiniCParser::AssignNoSemiContext>(0);
}


size_t MiniCParser::ForInitContext::getRuleIndex() const {
  return MiniCParser::RuleForInit;
}


std::any MiniCParser::ForInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitForInit(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ForInitContext* MiniCParser::forInit() {
  ForInitContext *_localctx = _tracker.createInstance<ForInitContext>(_ctx, getState());
  enterRule(_localctx, 28, MiniCParser::RuleForInit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(206);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T_INT: {
        enterOuterAlt(_localctx, 1);
        setState(204);
        varDeclNoSemi();
        break;
      }

      case MiniCParser::T_ID: {
        enterOuterAlt(_localctx, 2);
        setState(205);
        assignNoSemi();
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

//----------------- VarDeclNoSemiContext ------------------------------------------------------------------

MiniCParser::VarDeclNoSemiContext::VarDeclNoSemiContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::BasicTypeContext* MiniCParser::VarDeclNoSemiContext::basicType() {
  return getRuleContext<MiniCParser::BasicTypeContext>(0);
}

std::vector<MiniCParser::VarDefContext *> MiniCParser::VarDeclNoSemiContext::varDef() {
  return getRuleContexts<MiniCParser::VarDefContext>();
}

MiniCParser::VarDefContext* MiniCParser::VarDeclNoSemiContext::varDef(size_t i) {
  return getRuleContext<MiniCParser::VarDefContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::VarDeclNoSemiContext::T_COMMA() {
  return getTokens(MiniCParser::T_COMMA);
}

tree::TerminalNode* MiniCParser::VarDeclNoSemiContext::T_COMMA(size_t i) {
  return getToken(MiniCParser::T_COMMA, i);
}


size_t MiniCParser::VarDeclNoSemiContext::getRuleIndex() const {
  return MiniCParser::RuleVarDeclNoSemi;
}


std::any MiniCParser::VarDeclNoSemiContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitVarDeclNoSemi(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::VarDeclNoSemiContext* MiniCParser::varDeclNoSemi() {
  VarDeclNoSemiContext *_localctx = _tracker.createInstance<VarDeclNoSemiContext>(_ctx, getState());
  enterRule(_localctx, 30, MiniCParser::RuleVarDeclNoSemi);
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
    basicType();
    setState(209);
    varDef();
    setState(214);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_COMMA) {
      setState(210);
      match(MiniCParser::T_COMMA);
      setState(211);
      varDef();
      setState(216);
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

//----------------- AssignNoSemiContext ------------------------------------------------------------------

MiniCParser::AssignNoSemiContext::AssignNoSemiContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::LValContext* MiniCParser::AssignNoSemiContext::lVal() {
  return getRuleContext<MiniCParser::LValContext>(0);
}

tree::TerminalNode* MiniCParser::AssignNoSemiContext::T_ASSIGN() {
  return getToken(MiniCParser::T_ASSIGN, 0);
}

MiniCParser::ExprContext* MiniCParser::AssignNoSemiContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}


size_t MiniCParser::AssignNoSemiContext::getRuleIndex() const {
  return MiniCParser::RuleAssignNoSemi;
}


std::any MiniCParser::AssignNoSemiContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitAssignNoSemi(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::AssignNoSemiContext* MiniCParser::assignNoSemi() {
  AssignNoSemiContext *_localctx = _tracker.createInstance<AssignNoSemiContext>(_ctx, getState());
  enterRule(_localctx, 32, MiniCParser::RuleAssignNoSemi);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    lVal();
    setState(218);
    match(MiniCParser::T_ASSIGN);
    setState(219);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

MiniCParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::LogicalOrExpContext* MiniCParser::ExprContext::logicalOrExp() {
  return getRuleContext<MiniCParser::LogicalOrExpContext>(0);
}


size_t MiniCParser::ExprContext::getRuleIndex() const {
  return MiniCParser::RuleExpr;
}


std::any MiniCParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ExprContext* MiniCParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 34, MiniCParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
    logicalOrExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalOrExpContext ------------------------------------------------------------------

MiniCParser::LogicalOrExpContext::LogicalOrExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::LogicalAndExpContext *> MiniCParser::LogicalOrExpContext::logicalAndExp() {
  return getRuleContexts<MiniCParser::LogicalAndExpContext>();
}

MiniCParser::LogicalAndExpContext* MiniCParser::LogicalOrExpContext::logicalAndExp(size_t i) {
  return getRuleContext<MiniCParser::LogicalAndExpContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::LogicalOrExpContext::T_OR() {
  return getTokens(MiniCParser::T_OR);
}

tree::TerminalNode* MiniCParser::LogicalOrExpContext::T_OR(size_t i) {
  return getToken(MiniCParser::T_OR, i);
}


size_t MiniCParser::LogicalOrExpContext::getRuleIndex() const {
  return MiniCParser::RuleLogicalOrExp;
}


std::any MiniCParser::LogicalOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::LogicalOrExpContext* MiniCParser::logicalOrExp() {
  LogicalOrExpContext *_localctx = _tracker.createInstance<LogicalOrExpContext>(_ctx, getState());
  enterRule(_localctx, 36, MiniCParser::RuleLogicalOrExp);
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
    setState(223);
    logicalAndExp();
    setState(228);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_OR) {
      setState(224);
      match(MiniCParser::T_OR);
      setState(225);
      logicalAndExp();
      setState(230);
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

//----------------- LogicalAndExpContext ------------------------------------------------------------------

MiniCParser::LogicalAndExpContext::LogicalAndExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::RelExpContext *> MiniCParser::LogicalAndExpContext::relExp() {
  return getRuleContexts<MiniCParser::RelExpContext>();
}

MiniCParser::RelExpContext* MiniCParser::LogicalAndExpContext::relExp(size_t i) {
  return getRuleContext<MiniCParser::RelExpContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::LogicalAndExpContext::T_AND() {
  return getTokens(MiniCParser::T_AND);
}

tree::TerminalNode* MiniCParser::LogicalAndExpContext::T_AND(size_t i) {
  return getToken(MiniCParser::T_AND, i);
}


size_t MiniCParser::LogicalAndExpContext::getRuleIndex() const {
  return MiniCParser::RuleLogicalAndExp;
}


std::any MiniCParser::LogicalAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::LogicalAndExpContext* MiniCParser::logicalAndExp() {
  LogicalAndExpContext *_localctx = _tracker.createInstance<LogicalAndExpContext>(_ctx, getState());
  enterRule(_localctx, 38, MiniCParser::RuleLogicalAndExp);
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
    setState(231);
    relExp();
    setState(236);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_AND) {
      setState(232);
      match(MiniCParser::T_AND);
      setState(233);
      relExp();
      setState(238);
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

//----------------- RelExpContext ------------------------------------------------------------------

MiniCParser::RelExpContext::RelExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::AddExpContext *> MiniCParser::RelExpContext::addExp() {
  return getRuleContexts<MiniCParser::AddExpContext>();
}

MiniCParser::AddExpContext* MiniCParser::RelExpContext::addExp(size_t i) {
  return getRuleContext<MiniCParser::AddExpContext>(i);
}

std::vector<MiniCParser::RelOpContext *> MiniCParser::RelExpContext::relOp() {
  return getRuleContexts<MiniCParser::RelOpContext>();
}

MiniCParser::RelOpContext* MiniCParser::RelExpContext::relOp(size_t i) {
  return getRuleContext<MiniCParser::RelOpContext>(i);
}


size_t MiniCParser::RelExpContext::getRuleIndex() const {
  return MiniCParser::RuleRelExp;
}


std::any MiniCParser::RelExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitRelExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::RelExpContext* MiniCParser::relExp() {
  RelExpContext *_localctx = _tracker.createInstance<RelExpContext>(_ctx, getState());
  enterRule(_localctx, 40, MiniCParser::RuleRelExp);
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
    setState(239);
    addExp();
    setState(245);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2064384) != 0)) {
      setState(240);
      relOp();
      setState(241);
      addExp();
      setState(247);
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

//----------------- RelOpContext ------------------------------------------------------------------

MiniCParser::RelOpContext::RelOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::RelOpContext::T_LT() {
  return getToken(MiniCParser::T_LT, 0);
}

tree::TerminalNode* MiniCParser::RelOpContext::T_GT() {
  return getToken(MiniCParser::T_GT, 0);
}

tree::TerminalNode* MiniCParser::RelOpContext::T_LE() {
  return getToken(MiniCParser::T_LE, 0);
}

tree::TerminalNode* MiniCParser::RelOpContext::T_GE() {
  return getToken(MiniCParser::T_GE, 0);
}

tree::TerminalNode* MiniCParser::RelOpContext::T_EQ() {
  return getToken(MiniCParser::T_EQ, 0);
}

tree::TerminalNode* MiniCParser::RelOpContext::T_NE() {
  return getToken(MiniCParser::T_NE, 0);
}


size_t MiniCParser::RelOpContext::getRuleIndex() const {
  return MiniCParser::RuleRelOp;
}


std::any MiniCParser::RelOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitRelOp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::RelOpContext* MiniCParser::relOp() {
  RelOpContext *_localctx = _tracker.createInstance<RelOpContext>(_ctx, getState());
  enterRule(_localctx, 42, MiniCParser::RuleRelOp);
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
    setState(248);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2064384) != 0))) {
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

//----------------- AddExpContext ------------------------------------------------------------------

MiniCParser::AddExpContext::AddExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::MulExpContext *> MiniCParser::AddExpContext::mulExp() {
  return getRuleContexts<MiniCParser::MulExpContext>();
}

MiniCParser::MulExpContext* MiniCParser::AddExpContext::mulExp(size_t i) {
  return getRuleContext<MiniCParser::MulExpContext>(i);
}

std::vector<MiniCParser::AddOpContext *> MiniCParser::AddExpContext::addOp() {
  return getRuleContexts<MiniCParser::AddOpContext>();
}

MiniCParser::AddOpContext* MiniCParser::AddExpContext::addOp(size_t i) {
  return getRuleContext<MiniCParser::AddOpContext>(i);
}


size_t MiniCParser::AddExpContext::getRuleIndex() const {
  return MiniCParser::RuleAddExp;
}


std::any MiniCParser::AddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitAddExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::AddExpContext* MiniCParser::addExp() {
  AddExpContext *_localctx = _tracker.createInstance<AddExpContext>(_ctx, getState());
  enterRule(_localctx, 44, MiniCParser::RuleAddExp);
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
    setState(250);
    mulExp();
    setState(256);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_ADD

    || _la == MiniCParser::T_SUB) {
      setState(251);
      addOp();
      setState(252);
      mulExp();
      setState(258);
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

//----------------- AddOpContext ------------------------------------------------------------------

MiniCParser::AddOpContext::AddOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::AddOpContext::T_ADD() {
  return getToken(MiniCParser::T_ADD, 0);
}

tree::TerminalNode* MiniCParser::AddOpContext::T_SUB() {
  return getToken(MiniCParser::T_SUB, 0);
}


size_t MiniCParser::AddOpContext::getRuleIndex() const {
  return MiniCParser::RuleAddOp;
}


std::any MiniCParser::AddOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitAddOp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::AddOpContext* MiniCParser::addOp() {
  AddOpContext *_localctx = _tracker.createInstance<AddOpContext>(_ctx, getState());
  enterRule(_localctx, 46, MiniCParser::RuleAddOp);
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
    setState(259);
    _la = _input->LA(1);
    if (!(_la == MiniCParser::T_ADD

    || _la == MiniCParser::T_SUB)) {
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

//----------------- MulExpContext ------------------------------------------------------------------

MiniCParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::UnaryExpContext *> MiniCParser::MulExpContext::unaryExp() {
  return getRuleContexts<MiniCParser::UnaryExpContext>();
}

MiniCParser::UnaryExpContext* MiniCParser::MulExpContext::unaryExp(size_t i) {
  return getRuleContext<MiniCParser::UnaryExpContext>(i);
}

std::vector<MiniCParser::MulOpContext *> MiniCParser::MulExpContext::mulOp() {
  return getRuleContexts<MiniCParser::MulOpContext>();
}

MiniCParser::MulOpContext* MiniCParser::MulExpContext::mulOp(size_t i) {
  return getRuleContext<MiniCParser::MulOpContext>(i);
}


size_t MiniCParser::MulExpContext::getRuleIndex() const {
  return MiniCParser::RuleMulExp;
}


std::any MiniCParser::MulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitMulExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::MulExpContext* MiniCParser::mulExp() {
  MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, getState());
  enterRule(_localctx, 48, MiniCParser::RuleMulExp);
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
    setState(261);
    unaryExp();
    setState(267);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28672) != 0)) {
      setState(262);
      mulOp();
      setState(263);
      unaryExp();
      setState(269);
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

//----------------- MulOpContext ------------------------------------------------------------------

MiniCParser::MulOpContext::MulOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::MulOpContext::T_MUL() {
  return getToken(MiniCParser::T_MUL, 0);
}

tree::TerminalNode* MiniCParser::MulOpContext::T_DIV() {
  return getToken(MiniCParser::T_DIV, 0);
}

tree::TerminalNode* MiniCParser::MulOpContext::T_MOD() {
  return getToken(MiniCParser::T_MOD, 0);
}


size_t MiniCParser::MulOpContext::getRuleIndex() const {
  return MiniCParser::RuleMulOp;
}


std::any MiniCParser::MulOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitMulOp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::MulOpContext* MiniCParser::mulOp() {
  MulOpContext *_localctx = _tracker.createInstance<MulOpContext>(_ctx, getState());
  enterRule(_localctx, 50, MiniCParser::RuleMulOp);
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
    setState(270);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28672) != 0))) {
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

MiniCParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::UnaryExpContext::getRuleIndex() const {
  return MiniCParser::RuleUnaryExp;
}

void MiniCParser::UnaryExpContext::copyFrom(UnaryExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PrefixUnaryContext ------------------------------------------------------------------

MiniCParser::PrimaryExpContext* MiniCParser::PrefixUnaryContext::primaryExp() {
  return getRuleContext<MiniCParser::PrimaryExpContext>(0);
}

std::vector<tree::TerminalNode *> MiniCParser::PrefixUnaryContext::T_SUB() {
  return getTokens(MiniCParser::T_SUB);
}

tree::TerminalNode* MiniCParser::PrefixUnaryContext::T_SUB(size_t i) {
  return getToken(MiniCParser::T_SUB, i);
}

std::vector<tree::TerminalNode *> MiniCParser::PrefixUnaryContext::T_NOT() {
  return getTokens(MiniCParser::T_NOT);
}

tree::TerminalNode* MiniCParser::PrefixUnaryContext::T_NOT(size_t i) {
  return getToken(MiniCParser::T_NOT, i);
}

std::vector<tree::TerminalNode *> MiniCParser::PrefixUnaryContext::T_INC() {
  return getTokens(MiniCParser::T_INC);
}

tree::TerminalNode* MiniCParser::PrefixUnaryContext::T_INC(size_t i) {
  return getToken(MiniCParser::T_INC, i);
}

std::vector<tree::TerminalNode *> MiniCParser::PrefixUnaryContext::T_DEC() {
  return getTokens(MiniCParser::T_DEC);
}

tree::TerminalNode* MiniCParser::PrefixUnaryContext::T_DEC(size_t i) {
  return getToken(MiniCParser::T_DEC, i);
}

MiniCParser::PrefixUnaryContext::PrefixUnaryContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::PrefixUnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitPrefixUnary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PostfixUnaryContext ------------------------------------------------------------------

MiniCParser::PrimaryExpContext* MiniCParser::PostfixUnaryContext::primaryExp() {
  return getRuleContext<MiniCParser::PrimaryExpContext>(0);
}

std::vector<tree::TerminalNode *> MiniCParser::PostfixUnaryContext::T_INC() {
  return getTokens(MiniCParser::T_INC);
}

tree::TerminalNode* MiniCParser::PostfixUnaryContext::T_INC(size_t i) {
  return getToken(MiniCParser::T_INC, i);
}

std::vector<tree::TerminalNode *> MiniCParser::PostfixUnaryContext::T_DEC() {
  return getTokens(MiniCParser::T_DEC);
}

tree::TerminalNode* MiniCParser::PostfixUnaryContext::T_DEC(size_t i) {
  return getToken(MiniCParser::T_DEC, i);
}

MiniCParser::PostfixUnaryContext::PostfixUnaryContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::PostfixUnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitPostfixUnary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::FunctionCallContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

tree::TerminalNode* MiniCParser::FunctionCallContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

tree::TerminalNode* MiniCParser::FunctionCallContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

MiniCParser::RealParamListContext* MiniCParser::FunctionCallContext::realParamList() {
  return getRuleContext<MiniCParser::RealParamListContext>(0);
}

std::vector<tree::TerminalNode *> MiniCParser::FunctionCallContext::T_SUB() {
  return getTokens(MiniCParser::T_SUB);
}

tree::TerminalNode* MiniCParser::FunctionCallContext::T_SUB(size_t i) {
  return getToken(MiniCParser::T_SUB, i);
}

std::vector<tree::TerminalNode *> MiniCParser::FunctionCallContext::T_NOT() {
  return getTokens(MiniCParser::T_NOT);
}

tree::TerminalNode* MiniCParser::FunctionCallContext::T_NOT(size_t i) {
  return getToken(MiniCParser::T_NOT, i);
}

std::vector<tree::TerminalNode *> MiniCParser::FunctionCallContext::T_INC() {
  return getTokens(MiniCParser::T_INC);
}

tree::TerminalNode* MiniCParser::FunctionCallContext::T_INC(size_t i) {
  return getToken(MiniCParser::T_INC, i);
}

std::vector<tree::TerminalNode *> MiniCParser::FunctionCallContext::T_DEC() {
  return getTokens(MiniCParser::T_DEC);
}

tree::TerminalNode* MiniCParser::FunctionCallContext::T_DEC(size_t i) {
  return getToken(MiniCParser::T_DEC, i);
}

MiniCParser::FunctionCallContext::FunctionCallContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::UnaryExpContext* MiniCParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 52, MiniCParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(298);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MiniCParser::PrefixUnaryContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(275);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 39847936) != 0)) {
        setState(272);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 39847936) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(277);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(278);
      primaryExp();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MiniCParser::PostfixUnaryContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(279);
      primaryExp();
      setState(283);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MiniCParser::T_INC

      || _la == MiniCParser::T_DEC) {
        setState(280);
        _la = _input->LA(1);
        if (!(_la == MiniCParser::T_INC

        || _la == MiniCParser::T_DEC)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(285);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MiniCParser::FunctionCallContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(289);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 39847936) != 0)) {
        setState(286);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 39847936) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(291);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(292);
      match(MiniCParser::T_ID);
      setState(293);
      match(MiniCParser::T_L_PAREN);
      setState(295);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515435923458) != 0)) {
        setState(294);
        realParamList();
      }
      setState(297);
      match(MiniCParser::T_R_PAREN);
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

//----------------- PrimaryExpContext ------------------------------------------------------------------

MiniCParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::PrimaryExpContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

MiniCParser::ExprContext* MiniCParser::PrimaryExpContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

tree::TerminalNode* MiniCParser::PrimaryExpContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

MiniCParser::LValContext* MiniCParser::PrimaryExpContext::lVal() {
  return getRuleContext<MiniCParser::LValContext>(0);
}

tree::TerminalNode* MiniCParser::PrimaryExpContext::T_DECIMAL() {
  return getToken(MiniCParser::T_DECIMAL, 0);
}

tree::TerminalNode* MiniCParser::PrimaryExpContext::T_OCTAL() {
  return getToken(MiniCParser::T_OCTAL, 0);
}

tree::TerminalNode* MiniCParser::PrimaryExpContext::T_HEX() {
  return getToken(MiniCParser::T_HEX, 0);
}


size_t MiniCParser::PrimaryExpContext::getRuleIndex() const {
  return MiniCParser::RulePrimaryExp;
}


std::any MiniCParser::PrimaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitPrimaryExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::PrimaryExpContext* MiniCParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 54, MiniCParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(308);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T_L_PAREN: {
        enterOuterAlt(_localctx, 1);
        setState(300);
        match(MiniCParser::T_L_PAREN);
        setState(301);
        expr();
        setState(302);
        match(MiniCParser::T_R_PAREN);
        break;
      }

      case MiniCParser::T_ID: {
        enterOuterAlt(_localctx, 2);
        setState(304);
        lVal();
        break;
      }

      case MiniCParser::T_DECIMAL: {
        enterOuterAlt(_localctx, 3);
        setState(305);
        match(MiniCParser::T_DECIMAL);
        break;
      }

      case MiniCParser::T_OCTAL: {
        enterOuterAlt(_localctx, 4);
        setState(306);
        match(MiniCParser::T_OCTAL);
        break;
      }

      case MiniCParser::T_HEX: {
        enterOuterAlt(_localctx, 5);
        setState(307);
        match(MiniCParser::T_HEX);
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

//----------------- RealParamListContext ------------------------------------------------------------------

MiniCParser::RealParamListContext::RealParamListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::ExprContext *> MiniCParser::RealParamListContext::expr() {
  return getRuleContexts<MiniCParser::ExprContext>();
}

MiniCParser::ExprContext* MiniCParser::RealParamListContext::expr(size_t i) {
  return getRuleContext<MiniCParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::RealParamListContext::T_COMMA() {
  return getTokens(MiniCParser::T_COMMA);
}

tree::TerminalNode* MiniCParser::RealParamListContext::T_COMMA(size_t i) {
  return getToken(MiniCParser::T_COMMA, i);
}


size_t MiniCParser::RealParamListContext::getRuleIndex() const {
  return MiniCParser::RuleRealParamList;
}


std::any MiniCParser::RealParamListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitRealParamList(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::RealParamListContext* MiniCParser::realParamList() {
  RealParamListContext *_localctx = _tracker.createInstance<RealParamListContext>(_ctx, getState());
  enterRule(_localctx, 56, MiniCParser::RuleRealParamList);
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
    setState(310);
    expr();
    setState(315);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_COMMA) {
      setState(311);
      match(MiniCParser::T_COMMA);
      setState(312);
      expr();
      setState(317);
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

//----------------- LValContext ------------------------------------------------------------------

MiniCParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::LValContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

MiniCParser::ArrayIndexingContext* MiniCParser::LValContext::arrayIndexing() {
  return getRuleContext<MiniCParser::ArrayIndexingContext>(0);
}


size_t MiniCParser::LValContext::getRuleIndex() const {
  return MiniCParser::RuleLVal;
}


std::any MiniCParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::LValContext* MiniCParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 58, MiniCParser::RuleLVal);
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
    setState(318);
    match(MiniCParser::T_ID);
    setState(320);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T_L_BRACKET) {
      setState(319);
      arrayIndexing();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayIndexingContext ------------------------------------------------------------------

MiniCParser::ArrayIndexingContext::ArrayIndexingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MiniCParser::ArrayIndexingContext::T_L_BRACKET() {
  return getTokens(MiniCParser::T_L_BRACKET);
}

tree::TerminalNode* MiniCParser::ArrayIndexingContext::T_L_BRACKET(size_t i) {
  return getToken(MiniCParser::T_L_BRACKET, i);
}

std::vector<MiniCParser::ExprContext *> MiniCParser::ArrayIndexingContext::expr() {
  return getRuleContexts<MiniCParser::ExprContext>();
}

MiniCParser::ExprContext* MiniCParser::ArrayIndexingContext::expr(size_t i) {
  return getRuleContext<MiniCParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::ArrayIndexingContext::T_R_BRACKET() {
  return getTokens(MiniCParser::T_R_BRACKET);
}

tree::TerminalNode* MiniCParser::ArrayIndexingContext::T_R_BRACKET(size_t i) {
  return getToken(MiniCParser::T_R_BRACKET, i);
}


size_t MiniCParser::ArrayIndexingContext::getRuleIndex() const {
  return MiniCParser::RuleArrayIndexing;
}


std::any MiniCParser::ArrayIndexingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitArrayIndexing(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ArrayIndexingContext* MiniCParser::arrayIndexing() {
  ArrayIndexingContext *_localctx = _tracker.createInstance<ArrayIndexingContext>(_ctx, getState());
  enterRule(_localctx, 60, MiniCParser::RuleArrayIndexing);
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
    setState(326); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(322);
      match(MiniCParser::T_L_BRACKET);
      setState(323);
      expr();
      setState(324);
      match(MiniCParser::T_R_BRACKET);
      setState(328); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == MiniCParser::T_L_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void MiniCParser::initialize() {
  ::antlr4::internal::call_once(minicParserOnceFlag, minicParserInitialize);
}
