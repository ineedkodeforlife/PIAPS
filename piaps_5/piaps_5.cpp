#include <iostream>
#include <string>

class Text {
public:
    virtual void interpret(std::string& text) = 0;
};

class SpaceCorrector : public Text {
public:
    void interpret(std::string& text) override {
        size_t pos = 0;
        while ((pos = text.find("  ", pos)) != std::string::npos) {
            text.replace(pos, 2, " ");
            pos += 1;
        }
    }
};

class HyphenCorrector : public Text {
public:
    void interpret(std::string& text) override {
        size_t pos = 0;
        while ((pos = text.find("-", pos)) != std::string::npos) {
            text.replace(pos, 1, "—");
            pos += 1;
        }
    }
};

class QuoteCorrector : public Text {
public:
    void interpret(std::string& text) override {
        size_t pos = 0;
        while ((pos = text.find("«", pos)) != std::string::npos) {
            text.replace(pos, 1, "\"");
            pos += 1;
        }
        pos = 0;
        while ((pos = text.find("»", pos)) != std::string::npos) {
            text.replace(pos, 1, "\"");
            pos += 1;
        }
    }
};

class TabCorrector : public Text {
public:
    void interpret(std::string& text) override {
        size_t pos = 0;
        while ((pos = text.find("\t", pos)) != std::string::npos) {
            text.replace(pos, 1, " ");
            pos += 4; 
        }
    }
};

class SpaceBeforeBracketCorrector : public Text {
public:
    void interpret(std::string& text) override {
        size_t pos = 0;
        while ((pos = text.find("( ", pos)) != std::string::npos) {
            text.replace(pos, 2, "("); 
            pos += 1; 
        }
    }
};

class SpaceAfterBracketCorrector : public Text {
public:
    void interpret(std::string& text) override {
        size_t pos = 0;
        while ((pos = text.find(" )", pos)) != std::string::npos) {
            text.replace(pos, 2, ")"); 
            pos += 1; 
        }
    }
};

class SpaceBeforeCommaCorrector : public Text {
public:
    void interpret(std::string& text) override {
        size_t pos = 0;
        while ((pos = text.find(" ,", pos)) != std::string::npos) {
            text.replace(pos, 2, ","); 
            pos += 1; 
        }
    }
};

class SpaceBeforePeriodCorrector : public Text {
public:
    void interpret(std::string& text) override {
        size_t pos = 0;
        while ((pos = text.find(" .", pos)) != std::string::npos) {
            text.replace(pos, 2, ".");
            pos += 1;
        }
    }
};

class NewLineCorrector : public Text {
public:
    void interpret(std::string& text) override {
        size_t pos = 0;
        while ((pos = text.find("\n\n", pos)) != std::string::npos) {
            text.replace(pos, 2, "\n"); 
        }
    }
};



class TextCorrector {
private:
    SpaceCorrector spaceCorrector;
    HyphenCorrector hyphenCorrector;
    QuoteCorrector quoteCorrector;
    TabCorrector tabCorrector;
    SpaceBeforeCommaCorrector spaceBeforeCommaCorrector;
    SpaceBeforePeriodCorrector spaceBeforePeriodCorrector;
    NewLineCorrector newLineCorrector;
    SpaceBeforeBracketCorrector spacebeforebracketcorrector;
    SpaceAfterBracketCorrector spaceafterbracketcorrectorr;

public:
    void correctText(std::string& text) {
        spaceCorrector.interpret(text);
        hyphenCorrector.interpret(text);
        quoteCorrector.interpret(text);
        tabCorrector.interpret(text);
        spaceBeforeCommaCorrector.interpret(text);
        spaceBeforePeriodCorrector.interpret(text);
        newLineCorrector.interpret(text);
        spaceafterbracketcorrectorr.interpret(text);
        spacebeforebracketcorrector.interpret(text);

    }
};


int main() {


    TextCorrector textCorrector;

    std::string text = "This  is a  test text ,  with -- some\terrors .« There are a  few» errors .\n\nLet's see if all correctors can fix them!";

    textCorrector.correctText(text);

    std::cout << text << std::endl;

    return 0;
}