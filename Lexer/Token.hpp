#include <string>
#include <map>

class Token {
   public:
        enum class Kind {
            NUMBER,
            STRING,       // "ABC" || 'ABC'
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
            UNEXPECTED
        };

        Token(Kind kind, std::string const &lex) : _kind{kind}, _lexeme(lex) {}

        // Token(Kind kind) : _kind{kind} {}

        bool is(Kind kind) { return _kind == kind; }

        std::string const &kind() const {
            auto find = keyword_map.find(_lexeme);
            if (_kind == Kind:IDENTIFIER && find != keyword_map.end()) {
                return find->second;
            }   

            return token_map.find(_kind)->second;; 
        }
        std::string const &lexeme() const { return _lexeme; }

    private:
        Kind _kind{};
        std::string _lexeme{};

        std::map<Kind, std::string> token_map {
            { Kind::NUMBER,           "NUMBER" },
            { Kind::STRING,           "STRING" },
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
            { Kind::UNEXPECTED,       "UNEXPECTED" }
        };

        std::map<std::string, std::string> keyword_map {

        };
};
