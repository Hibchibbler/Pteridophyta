#ifndef LoaderXML_h_
#define LoaderXML_h_

//This is a convienance macro for assigning attributes while parsing XML
#define ASSIGNIFMATCHES(a1, a2)                     \
        if (std::string(attribute[i]) == a1){       \
            a2 = attribute[i+1];                    \
            continue;                               \
        }


namespace bali{


class LoaderXML
{
public:
    LoaderXML(){}
    ~LoaderXML(){}

    typedef void (*StartElement) (void* data, const char* element, const char** attribute);
    typedef void (*EndElement) (void* data, const char* el);

public:
    static bool load(const char *fn, void *ud, StartElement se, EndElement ee);

private:

};//end class LoaderXML


}//end namespace bali


#endif

