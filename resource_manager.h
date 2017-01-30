class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    int loadTextureFromPNG(const std::string& filename);
    int makeCheckerboardTexture(int width, int height, int steps);

    uint8_t* getTextureData(int handle);
    int getTextureWidth(int handle);
    int getTextureHeight(int handle);

private:
    int _nextFreeHandle;

    std::map<int, uint8_t*> _textureData;
    std::map<int, int> _textureWidths;
    std::map<int, int> _textureHeights;
}

