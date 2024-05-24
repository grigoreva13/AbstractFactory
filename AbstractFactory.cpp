/*
Вариант 13. Разработайте иерархию классов: «Средства разработки»
(конкретные классы «Delphi», «Visual Studio»), «Операционные системы» («Win XP», «Win
8»). Delphi может функционировать только под управлением ОС WinXP (семейство «старых»
лицензированных программ), Visual Studio – только под управлением Win 8 (семейство
«новых» лицензированных программ). Реализуйте данную ситуацию при помощи паттерна
Abstract Factory. Добавьте также еще один продукт (например, компиляторы — Borland для
«старых» лицензий, Visual — для «новых»), и семейство средств с открытой лицензией (ОС
Linux, IDE NetBeans, компиляторы MinGW).
*/

#include <iostream>
#include <string>

// Абстрактные классы для средств разработки
class IDE {
public:
    virtual void info() = 0;
    virtual ~IDE() {}
};

class Compiler {
public:
    virtual void info() = 0;
    virtual ~Compiler() {}
};

// Абстрактная фабрика
class AbstractFactory {
public:
    virtual IDE* createIDE() = 0;
    virtual Compiler* createCompiler() = 0;
    virtual ~AbstractFactory() {}
};

// Конкретные классы средств разработки
class DelphiIDE : public IDE {
public:
    void info() override {
        std::cout << "Delphi IDE поддерживается только на Windows XP" << std::endl;
    }
};

class VisualStudioIDE : public IDE {
public:
    void info() override {
        std::cout << "Visual Studio поддерживается только на Windows 8" << std::endl;
    }
};

// Конкретные классы компиляторов
class BorlandCompiler : public Compiler {
public:
    void info() override {
        std::cout << "Borland Compiler для старых лицензий" << std::endl;
    }
};

class VisualCompiler : public Compiler {
public:
    void info() override {
        std::cout << "Visual Compiler для новых лицензий" << std::endl;
    }
};

// Конкретные фабрики
class WinXPFactory : public AbstractFactory {
public:
    IDE* createIDE() override {
        return new DelphiIDE();
    }

    Compiler* createCompiler() override {
        return new BorlandCompiler();
    }
};

class Win8Factory : public AbstractFactory {
public:
    IDE* createIDE() override {
        return new VisualStudioIDE();
    }

    Compiler* createCompiler() override {
        return new VisualCompiler();
    }
};

// Пример использования
int main() {
    setlocale(LC_ALL, "Russian");
    AbstractFactory* winXpFactory = new WinXPFactory();
    AbstractFactory* win8Factory = new Win8Factory();

    IDE* delphiIDE = winXpFactory->createIDE();
    Compiler* borlandCompiler = winXpFactory->createCompiler();

    IDE* vsIDE = win8Factory->createIDE();
    Compiler* visualCompiler = win8Factory->createCompiler();

    delphiIDE->info();
    borlandCompiler->info();

    vsIDE->info();
    visualCompiler->info();

    delete delphiIDE;
    delete borlandCompiler;
    delete vsIDE;
    delete visualCompiler;

    delete winXpFactory;
    delete win8Factory;

    return 0;
}