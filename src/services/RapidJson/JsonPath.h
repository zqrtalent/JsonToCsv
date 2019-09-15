#ifndef JSON_PATH_H_INCLUDED
#define JSON_PATH_H_INCLUDED

#include <iostream>
using namespace std;

struct JsonPath {
    enum ComponentType{
        JObject = 0,
        JProperty,
        JArray,
        JarrayElement
    };

    struct PathComponent{
    public:
        PathComponent(){ next = prev = nullptr; }
        PathComponent(const PathComponent& init){
            path = init.path;
            type = init.type;
            index = init.index;
            next = prev = nullptr;
        }

        PathComponent& operator=(const PathComponent& init){
            path = init.path;
            type = init.type;
            index = init.index;
            next = prev = nullptr;
            return *this;
        }

        std::string path;
        ComponentType type;
        int index; // Array item index
        struct PathComponent* next;
        struct PathComponent* prev;
    };

    PathComponent* head;
    PathComponent* tail;

    string path;
    bool recalcPath;

    JsonPath(){
        head = tail = nullptr;
        recalcPath = false;
    }

    ~JsonPath(){
        DeleteAll();
    }

    bool Push(const std::string path, ComponentType type, int index = 0){
        if(path.empty())
            return false;
        auto newEntry = new PathComponent();
        newEntry->path = path;
        newEntry->type = type;
        newEntry->index = index;
        newEntry->next  = nullptr;

        if(!head)
            head = newEntry;
        if(tail)
            tail->next = newEntry;
        newEntry->prev = tail;
        tail = newEntry;
        recalcPath = true;
        return true;
    }

    bool Pop(PathComponent& newTail){
        if(!tail){
            return false;
        }
        auto tailNew = tail->prev;
        delete tail;
        tail = tailNew;
        
        if(tail == nullptr)
            head = nullptr;
        else
            tail->next = nullptr;
        recalcPath = true;

        if(tail)
            newTail = PathComponent(*tail);
        return true;
    }

    void SetTailIndex(int arrayIndex){
        if(tail)
            tail->index = arrayIndex;
    }

    std::string CombinePath(const string& path){
        if(tail == nullptr)
            return path;
        return GetPath() + "." + path;
    }

    std::string GetPath(){
        if(!recalcPath)
            return path;

        std::string path;
        auto curr = head;
        while (curr){
            path += curr->path;
            if(curr != tail)
                path += ".";
            curr = curr->next;
        }
        this->path = path;
        recalcPath = false;
        return path;
    }

    void DeleteAll(){
        auto curr = head;
        while(curr != nullptr){
            auto next = curr->next;
            delete curr;
            curr = next;
        }

        head = tail = nullptr;
        recalcPath = false;
        path = "";
    }
};

#endif //JSON_PATH_H_INCLUDED

