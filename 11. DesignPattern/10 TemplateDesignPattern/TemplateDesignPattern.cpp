// pipeline Pattern

#include <iostream>
#include <memory>
using namespace std;

class ModelTrainer{
    public:
    virtual ~ModelTrainer(){}
    void TemplateMethod(const string &st){
        load(st);
        prepare();
        train();
        evalute();
        save();
    }
    protected:
    virtual void load(const string &st){
        cout<<"[C] Loading Data From" << st << endl;
    }

    virtual void prepare() = 0;
    virtual void train() = 0;
    virtual void evalute() = 0;
    
    virtual void save(){
        cout<<"[C] Saving Model" << endl;
    }
};

class NeuralNetwork : public ModelTrainer{
    public:
    void prepare(){
        cout<<"[N] Neural Network Preparing Data" << endl;
    }

    void train(){
        cout<<"[N] Neural Network Training" << endl;
    }
    void evalute(){
        cout<<"[N] Neural Network Evaluating" << endl;
    }
    
    void save(){
        cout<<"[N] Neural Network Saving Model" << endl;
    }
};

class DecisionTree : public ModelTrainer{
    public:
    void prepare(){
        cout<<"[N] Neural Network Preparing Data" << endl;
    }
    void train(){
        cout<<"[N] Neural Network Training" << endl;
    }
    void evalute(){
        cout<<"[N] Neural Network Evaluating" << endl;
    }
};

int main(){
    unique_ptr<ModelTrainer> nn = make_unique<NeuralNetwork>();
    unique_ptr<ModelTrainer> dt = make_unique<DecisionTree>();

    nn->TemplateMethod("/data/nn_set");
    cout << "---" << endl;
    dt->TemplateMethod("/data/dt_set");

    return 0;
}
