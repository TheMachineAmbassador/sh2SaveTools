#include "MemoryViewer.h"

#include <DecryptSave.h>

extern SaveFileBlocks fileBlock;

void MemoryViewer::DrawMemoryEditor()
{
    Cols = 32;
    OptShowDataPreview = true;
    OptGreyOutZeroes = false;

    DrawWindow("MemoryEditor", &fileBlock, sizeof(SaveFileBlocks));
}
