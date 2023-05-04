#include <string>
#include <map>

class Token {
   public:
        enum class Kind {
            NUMBER,
            STRING,       // "ABC" || 'ABC'
            CHARACTER,
            IDENTIFIER,
            LEFT_PAREN,   // (
            RIGHT_PAREN,  // )
            LEFT_SQUARE,  // [
            RIGHT_SQUARE, // ]
            LEFT_CURLY,   // {
            RIGHT_CURLY,  // }
            LESS_THEN,    // <
            GREATER_THEN, // >
            EQUAL,        // =
            NOT_EQUAL,    // !=
            PLUS,         // +
            MINUS,        // -
            ASTERISK,     // *
            SLASH,        // /
            PERCENT,      // %
            HASH,         // #
            DOT,          // .
            COMMA,        // ,
            COLON,        // :
            SEMICOLON,    // ;
            DOUBLE_SEMICOLON,// ;;
            SINGLE_QUOTE, // '
            DOUBLE_QUOTE, // "
            PIPE,         // |
            TILDE,        // ~
            CARET,        // ^
            ARROW,        // ->
            DOUBLE_EQUAL, // ==
            OR,           // ||
            AND,          // &&
            COMMENT,      // ([*]+ comment here [*]+) (* cmt *)
            END,
            UNEXPECTED_TOKEN,
            UNEXPECTED_SYMBOL,

            //KEYWORDS
            KW_AND,
            KW_AS,
            KW_ASSERT,
            KW_ASR,
            KW_BEGIN,
            KW_CLASS,
            KW_CONSTRAINT,
            KW_DO,
            KW_DONE,
            KW_DOWNTO,
            KW_ELSE,
            KW_END,
            KW_EXCEPTION,
            KW_EXTERNAL,
            KW_FALSE,
            KW_FOR,
            KW_FUN,
            KW_FUNCTION,
            KW_FUNCTOR,
            KW_IF,
            KW_IN,
            KW_INCLUDE,
            KW_INHERIT,
            KW_INITIALIZER,
            KW_LAZY,
            KW_LET,
            KW_MATCH,
            KW_METHOD,
            KW_MOD,
            KW_MODULE,
            KW_MUTABLE,
            KW_NEW,
            KW_NONREC,
            KW_OBJECT,
            KW_OF,
            KW_OPEN,
            KW_OR,
            KW_PRIVATE,
            KW_REC,
            KW_SIG,
            KW_STRUCT,
            KW_THEN,
            KW_TO,
            KW_TRUE,
            KW_TRY,
            KW_TYPE,
            KW_VAL,
            KW_VIRTUAL,
            KW_WHEN,
            KW_WHILE,
            KW_WITH
        };

        Token(Kind kind, std::string const &lex) : _kind{kind}, _lexeme(lex) {
            if (_kind == Kind::IDENTIFIER && keyword_map.count(lex)) {
                auto find = keyword_map.find(lex);
                _kind = find->second;
            }
        }

        // Token(Kind kind) : _kind{kind} {}

        bool is(Kind kind) { return _kind == kind; }

        std::string const &kind() const {
            return token_map.find(_kind)->second;; 
        }
        std::string const &lexeme() const { return _lexeme; }

    private:
        Kind _kind{};
        std::string _lexeme{};

        std::map<Kind, std::string> token_map {
            { Kind::NUMBER,           "NUMBER" },
            { Kind::STRING,           "STRING" },
            { Kind::CHARACTER,        "CHARACTER" },
            { Kind::IDENTIFIER,       "IDENTIFIER" },
            { Kind::LEFT_PAREN,       "LEFT_PAREN" },
            { Kind::RIGHT_PAREN,      "RIGHT_PAREN" },
            { Kind::LEFT_SQUARE,      "LEFT_SQUARE" },
            { Kind::RIGHT_SQUARE,     "RIGHT_SQUARE" },
            { Kind::LEFT_CURLY,       "LEFT_CURLY" },
            { Kind::RIGHT_CURLY,      "RIGHT_CURLY" },
            { Kind::LESS_THEN,        "LESS_THEN" },
            { Kind::GREATER_THEN,     "GREATER_THEN" },
            { Kind::EQUAL,            "EQUAL" },
            { Kind::NOT_EQUAL,        "NOT_EQUAL" },
            { Kind::PLUS,             "PLUS" },
            { Kind::MINUS,            "MINUS" },
            { Kind::ASTERISK,         "ASTERISK" },
            { Kind::SLASH,            "SLASH" },
            { Kind::PERCENT,          "PERCENT" },
            { Kind::HASH,             "HASH" },
            { Kind::DOT,              "DOT" },
            { Kind::COMMA,            "COMMA" },
            { Kind::COLON,            "COLON" },
            { Kind::SEMICOLON,        "SEMICOLON" },
            { Kind::DOUBLE_SEMICOLON, "DOUBLE_SEMICOLON" },
            { Kind::SINGLE_QUOTE,     "SINGLE_QUOTE" },
            { Kind::DOUBLE_QUOTE,     "DOUBLE_QUOTE" },
            { Kind::PIPE,             "PIPE" },
            { Kind::TILDE,            "TILDE" },
            { Kind::CARET,            "CARET" },
            { Kind::ARROW,            "ARROW" },
            { Kind::DOUBLE_EQUAL,     "DOUBLE_EQUAL" },
            { Kind::OR,               "OR" },
            { Kind::AND,              "AND" },
            { Kind::COMMENT,          "COMMENT" },
            { Kind::END,              "END" },
            { Kind::UNEXPECTED,       "UNEXPECTED" },

            //keywords token map
            { Kind::KW_AND,         "KEYWORD__AND" },
            { Kind::KW_AS,          "KEYWORD__AS" },
            { Kind::KW_ASSERT,      "KEYWORD__ASSERT" },
            { Kind::KW_ASR,         "KEYWORD__ASR" },
            { Kind::KW_BEGIN,       "KEYWORD__BEGIN" },
            { Kind::KW_CLASS,       "KEYWORD__CLASS" },
            { Kind::KW_CONSTRAINT,  "KEYWORD__CONSTRAINT" },
            { Kind::KW_DO,          "KEYWORD__DO" },
            { Kind::KW_DONE,        "KEYWORD__DONE" },
            { Kind::KW_DOWNTO,      "KEYWORD__DOWNTO" },
            { Kind::KW_ELSE,        "KEYWORD__ELSE" },
            { Kind::KW_END,         "KEYWORD__END" },
            { Kind::KW_EXCEPTION,   "KEYWORD__EXCEPTION" },
            { Kind::KW_EXTERNAL,    "KEYWORD__EXTERNAL" },
            { Kind::KW_FALSE,       "KEYWORD__FALSE" },
            { Kind::KW_FOR,         "KEYWORD__FOR" },
            { Kind::KW_FUN,         "KEYWORD__FUN" },
            { Kind::KW_FUNCTION,    "KEYWORD__FUNCTION" },
            { Kind::KW_FUNCTOR,     "KEYWORD__FUNCTOR" },
            { Kind::KW_IF,          "KEYWORD__IF" },
            { Kind::KW_IN,          "KEYWORD__IN" },
            { Kind::KW_INCLUDE,     "KEYWORD__INCLUDE" },
            { Kind::KW_INHERIT,     "KEYWORD__INHERIT" },
            { Kind::KW_INITIALIZER, "KEYWORD__INITIALIZER" },
            { Kind::KW_LAZY,        "KEYWORD__LAZY" },
            { Kind::KW_LET,         "KEYWORD__LET" },
            { Kind::KW_MATCH,       "KEYWORD__MATCH" },
            { Kind::KW_METHOD,      "KEYWORD__METHOD" },
            { Kind::KW_MOD,         "KEYWORD__MOD" },
            { Kind::KW_MODULE,      "KEYWORD__MODULE" },
            { Kind::KW_MUTABLE,     "KEYWORD__MUTABLE" },
            { Kind::KW_NEW,         "KEYWORD__NEW" },
            { Kind::KW_NONREC,      "KEYWORD__NONREC" },
            { Kind::KW_OBJECT,      "KEYWORD__OBJECT" },
            { Kind::KW_OF,          "KEYWORD__OF" },
            { Kind::KW_OPEN,        "KEYWORD__OPEN" },
            { Kind::KW_OR,          "KEYWORD__OR" },
            { Kind::KW_PRIVATE,     "KEYWORD__PRIVATE" },
            { Kind::KW_REC,         "KEYWORD__REC" },
            { Kind::KW_SIG,         "KEYWORD__SIG" },
            { Kind::KW_STRUCT,      "KEYWORD__STRUCT" },
            { Kind::KW_THEN,        "KEYWORD__THEN" },
            { Kind::KW_TO,          "KEYWORD__TO" },
            { Kind::KW_TRUE,        "KEYWORD__TRUE" },
            { Kind::KW_TRY,         "KEYWORD__TRY" },
            { Kind::KW_TYPE,        "KEYWORD__TYPE" },
            { Kind::KW_VAL,         "KEYWORD__VAL" },
            { Kind::KW_VIRTUAL,     "KEYWORD__VIRTUAL" },
            { Kind::KW_WHEN,        "KEYWORD__WHEN" },
            { Kind::KW_WHILE,       "KEYWORD__WHILE" },
            { Kind::KW_WITH,        "KEYWORD__WITH" },
        };

        std::map<std::string, Kind> keyword_map {
            { "and",         Kind::KW_AND },
            { "as",          Kind::KW_AS },
            { "assert",      Kind::KW_ASSERT },
            { "asr",         Kind::KW_ASR },
            { "begin",       Kind::KW_BEGIN },
            { "class",       Kind::KW_CLASS },
            { "constraint",  Kind::KW_CONSTRAINT },
            { "do",          Kind::KW_DO },
            { "done",        Kind::KW_DONE },
            { "downto",      Kind::KW_DOWNTO },
            { "else",        Kind::KW_ELSE },
            { "end",         Kind::KW_END },
            { "exception",   Kind::KW_EXCEPTION },
            { "external",    Kind::KW_EXTERNAL },
            { "false",       Kind::KW_FALSE },
            { "for",         Kind::KW_FOR },
            { "fun",         Kind::KW_FUN },
            { "function",    Kind::KW_FUNCTION },
            { "functor",     Kind::KW_FUNCTOR },
            { "if",          Kind::KW_IF },
            { "in",          Kind::KW_IN },
            { "include",     Kind::KW_INCLUDE },
            { "inherit",     Kind::KW_INHERIT },
            { "initializer", Kind::KW_INITIALIZER },
            { "lazy",        Kind::KW_LAZY },
            { "let",         Kind::KW_LET },
            { "match",       Kind::KW_MATCH },
            { "method",      Kind::KW_METHOD },
            { "mod",         Kind::KW_MOD },
            { "module",      Kind::KW_MODULE },
            { "mutable",     Kind::KW_MUTABLE },
            { "new",         Kind::KW_NEW },
            { "nonrec",      Kind::KW_NONREC },
            { "object",      Kind::KW_OBJECT },
            { "of",          Kind::KW_OF },
            { "open",        Kind::KW_OPEN },
            { "or",          Kind::KW_OR },
            { "private",     Kind::KW_PRIVATE },
            { "rec",         Kind::KW_REC },
            { "sig",         Kind::KW_SIG },
            { "struct",      Kind::KW_STRUCT },
            { "then",        Kind::KW_THEN },
            { "to",          Kind::KW_TO },
            { "true",        Kind::KW_TRUE },
            { "try",         Kind::KW_TRY },
            { "type",        Kind::KW_TYPE },
            { "val",         Kind::KW_VAL },
            { "virtual",     Kind::KW_VIRTUAL },
            { "when",        Kind::KW_WHEN },
            { "while",       Kind::KW_WHILE },
            { "with",        Kind::KW_WITH }
        };
};
