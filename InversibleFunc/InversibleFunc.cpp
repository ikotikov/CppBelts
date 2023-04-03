#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// struct Image {
//   double quality;
//   double freshness;
//   double rating;
// };

// struct Params {
//   double a;
//   double b;
//   double c;
// };

class FunctionPart
{
private:
    char operation;
    double number;
public:
    FunctionPart(char new_operation, double new_number) 
    {
        operation = new_operation;
        number = new_number;
    };
    double Apply (double source_number) const 
    {
        if (operation == '+')
        {
            return source_number + number;
        } else if (operation == '-')
        {
            return source_number - number;
        } else if (operation == '*')
        {
            return source_number * number;
        } else 
        {
            return source_number / number;
        }
        
    }
    void Invert ()
    {
        if (operation == '+')
        {
            operation =  '-';
        } else if (operation == '*')
        {
            operation = '/';
        } else if (operation == '-')
        {
            operation = '+';
        } else if (operation == '/')
        {
            operation = '*';
        }
        
        
    }
};

class Function
{
private:
    vector<FunctionPart> parts;
public:
    void AddPart (char operation, double number)
    {
        parts.push_back({operation, number});
    }
    double Apply (double number) const
    {
        for (const FunctionPart& part : parts)
        {
            number = part.Apply(number);
        }
        return number;
    }
    void Invert ()
    {
        for (FunctionPart& part : parts)
        {
            part.Invert();
        }
        reverse(begin(parts),end(parts));
    }
};

 Function MakeWeightFunction(const Params& params,
                             const Image& image) {
   Function function;
   function.AddPart('*', params.a);
   function.AddPart('-', image.freshness * params.b);
   function.AddPart('+', image.rating * params.c);
   return function;
 }

 double ComputeImageWeight(const Params& params, const Image& image) {
   Function function = MakeWeightFunction(params, image);
   return function.Apply(image.quality);
 }

 double ComputeQualityByWeight(const Params& params,
                               const Image& image,
                               double weight) {
   Function function = MakeWeightFunction(params, image);
   function.Invert();
   return function.Apply(weight);
 }

 int main()
 {
   Image image = {10, 2, 6};
   Params params = {4, 2, 6};
   cout << ComputeImageWeight(params, image) << endl;
   cout << ComputeQualityByWeight(params, image, 52) << endl;
   return 0;
 }
