#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
using namespace std;

int main(int argc, char *argv[argc])
{
    glm::vec4 vec(1.0f, 0.0f, 0.0f , 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);

    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    cout << vec.x << vec.y << vec.z << endl;
    return 0;
}
