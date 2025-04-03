#pragma once

#include <string>
#include <dlfcn.h>
#include <iostream>
#include <type_traits>

template<typename T>
struct LibraryFunctions {
    static const char* getCreateFunctionName() { return "createLib"; }
    static const char* getDestroyFunctionName() { return "destroyLib"; }
};

template<>
struct LibraryFunctions<IGraphicsLib> {
    static const char* getCreateFunctionName() { return "createGraphicsLib"; }
    static const char* getDestroyFunctionName() { return "destroyGraphicsLib"; }
};

template<>
struct LibraryFunctions<IGameLib> {
    static const char* getCreateFunctionName() { return "createGameLib"; }
    static const char* getDestroyFunctionName() { return "destroyGameLib"; }
};

template<typename T>
class DLLoader {
private:
    void* handle;
    T* instance;

public:
    DLLoader() : handle(nullptr), instance(nullptr) {}
    
    ~DLLoader() {
        closeLibrary();
    }
    
    bool loadLibrary(const std::string& path) {
        if (handle != nullptr) {
            closeLibrary();
        }
        
        handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Error: " << dlerror() << std::endl;
            return false;
        }
        const char* createFuncName = LibraryFunctions<T>::getCreateFunctionName();
        
        using CreateFunction = T* (*)();
        CreateFunction createFunction = reinterpret_cast<CreateFunction>(
            dlsym(handle, createFuncName)
        );
        
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Error loading symbol: " << dlsym_error << std::endl;
            dlclose(handle);
            handle = nullptr;
            return false;
        }
        
        instance = createFunction();
        return true;
    }
    
    T* getInstance() const {
        return instance;
    }
    
    void closeLibrary() {
        if (instance != nullptr) {
            const char* destroyFuncName = LibraryFunctions<T>::getDestroyFunctionName();
            
            using DestroyFunction = void (*)(T*);
            DestroyFunction destroyFunction = reinterpret_cast<DestroyFunction>(
                dlsym(handle, destroyFuncName)
            );
            
            if (destroyFunction) {
                destroyFunction(instance);
            }
            
            instance = nullptr;
        }
        
        if (handle != nullptr) {
            dlclose(handle);
            handle = nullptr;
        }
    }
};