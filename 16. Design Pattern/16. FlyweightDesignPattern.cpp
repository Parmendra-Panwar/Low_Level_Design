#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class GrassFlyweight{
public:
    string texture;
    string direction;
    double height;
    
    GrassFlyweight(string texture, string direction, double height){
        this->texture = texture;
        this->direction = direction;
        this->height = height;
    }

    void render(){
        cout<<texture<<" "<<" "<<direction<<" "<<height;
    }
};
class GrassFactory{
private:
    static unordered_map <string, GrassFlyweight*> Grasses;
public:
    static GrassFlyweight* getGrassFlyweight(string texture, string direction, double height){
        string id = texture + "_" + direction + "_" + to_string(height);
        GrassFlyweight* gF;
        if(Grasses.find(id) != Grasses.end()) gF = Grasses[id]; 
        else{
            gF =  new GrassFlyweight(texture, direction, height);
            Grasses[id] = gF;
        }
        return gF;
    };

    static void cleanup() {
        for (auto& pair : Grasses) {
            delete pair.second;
        }
        Grasses.clear();
    }
};
unordered_map<string, GrassFlyweight*> GrassFactory::Grasses;


class GrassContext{
public:
    GrassFlyweight* gF;
    double intensity;
    GrassContext(GrassFlyweight* gF, double intensity){
        this->gF = gF;
        this->intensity = intensity;
    }
    void render(){
        gF->render();
        cout<<intensity<<endl;
    }
};


int main(){
    vector<string> textures = {"darkGreen", "lightGreen", "brown", "muddy"};
    vector<string> directions = {"left", "right", "leftRight", "rightleft"};
    vector<double> heights = {11.1, 12.55, 12.1, 10.9};
    
    vector<GrassContext*> realGrass;
    for(int i = 0; i < 100; i++){
        GrassFlyweight* flyWe = GrassFactory::getGrassFlyweight(textures[i%4], directions[i%4], heights[i%4]);
        realGrass.push_back(new GrassContext(flyWe, i));
    }

    for(int i=0; i<4; i++)
    realGrass[i]->render();
    
    GrassFactory::cleanup();
    
    for(int i=0; i<100; i++)
    delete realGrass[i];
    return 0;
}