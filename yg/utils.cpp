#include "defines.hpp"
#include "utils.hpp"

#include "internal/opengl.hpp"

#include "../std/target_os.hpp"

namespace yg
{
  namespace gl
  {
    namespace utils
    {
      void setupCoordinates(size_t width, size_t height, bool doSwap /*= true*/)
      {
        OGLCHECK(glViewport(0, 0, width, height));

        OGLCHECK(glMatrixMode(GL_MODELVIEW));
        OGLCHECK(glLoadIdentity());

        OGLCHECK(glMatrixMode(GL_PROJECTION));
        OGLCHECK(glLoadIdentity());

#ifdef OMIM_GL_ES
        if (!doSwap)
          OGLCHECK(glOrthof(0, width, 0, height, -yg::maxDepth, yg::maxDepth));
        else
          OGLCHECK(glOrthof(0, width, height, 0, -yg::maxDepth, yg::maxDepth));
#else
        if (!doSwap)
          OGLCHECK(glOrtho(0, width, 0, height, -yg::maxDepth, yg::maxDepth));
        else
          OGLCHECK(glOrtho(0, width, height, 0, -yg::maxDepth, yg::maxDepth));
#endif
      }
    }
  }
}
