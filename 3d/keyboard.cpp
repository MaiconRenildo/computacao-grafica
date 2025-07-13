
void keyboard(int key, int x, int y) {
    float step = 0.3;
    float newX = motherPenguinX;
    float newZ = motherPenguinZ;
    bool movedOrChangedDirection = false;

    // Se estiver no modo de todas as viewports, o movimento se aplica à câmera de perspectiva.
    // Caso contrário, o movimento é específico da viewport ativa.
    int currentActiveViewport = showAllViewports ? 3 : activeViewport; 

    switch(currentActiveViewport) {
        case 0: // Câmera no Eixo X (visão lateral)
            // Aqui, o eixo X do mundo é o que aponta para a direita/esquerda na tela.
            // O eixo Z do mundo é o que aponta para dentro/fora da tela (profundidade).
            // Para um movimento intuitivo, Cima/Baixo devem mover em Z, Esquerda/Direita devem mover em X.
            switch(key) {
                case GLUT_KEY_UP: // "Para cima" na tela (em Z positivo)
                    newX -= step;
                    penguimRotationAngle = -90.0; // Pinguim olhando para X negativo
                    direcaoAtualPinguim = FACING_RIGHT; // O pinguim estará virado para a "direita" (X negativo)
                    break;
                case GLUT_KEY_DOWN: // "Para baixo" na tela (em Z negativo)
                    newX += step;
                    penguimRotationAngle = 90.0; // Pinguim olhando para X positivo
                    direcaoAtualPinguim = FACING_LEFT; // O pinguim estará virado para a "esquerda" (X positivo)
                    break;
                case GLUT_KEY_LEFT: // "Para a esquerda" na tela (em X negativo)
                    newZ += step;
                    penguimRotationAngle = 0.0; // Pinguim olhando para Z positivo
                    direcaoAtualPinguim = FACING_FORWARD;
                    break;
                case GLUT_KEY_RIGHT: // "Para a direita" na tela (em X positivo)
                    newZ -= step;
                    penguimRotationAngle = 180.0; // Pinguim olhando para Z negativo
                    direcaoAtualPinguim = FACING_BACKWARD;
                    break;
            }
            break;
        case 1: // Câmera no Eixo Y (visão de cima)
            // Nesta vista, o plano XY está visível. Z é a profundidade.
            // Cima/Baixo devem mover em Z, Esquerda/Direita devem mover em X.
            switch(key) {
                case GLUT_KEY_UP: // "Para cima" na tela (em Z positivo)
                    newZ -= step;
                    penguimRotationAngle = 180.0; // Pinguim olhando para Z negativo
                    direcaoAtualPinguim = FACING_BACKWARD;
                    break;
                case GLUT_KEY_DOWN: // "Para baixo" na tela (em Z negativo)
                    newZ += step;
                    penguimRotationAngle = 0.0; // Pinguim olhando para Z positivo
                    direcaoAtualPinguim = FACING_FORWARD;
                    break;
                case GLUT_KEY_LEFT: // "Para a esquerda" na tela (em X negativo)
                    newX -= step;
                    penguimRotationAngle = -90.0; // Pinguim olhando para X negativo
                    direcaoAtualPinguim = FACING_RIGHT;
                    break;
                case GLUT_KEY_RIGHT: // "Para a direita" na tela (em X positivo)
                    newX += step;
                    penguimRotationAngle = 90.0; // Pinguim olhando para X positivo
                    direcaoAtualPinguim = FACING_LEFT;
                    break;
            }
            break;
        case 2: // Câmera no Eixo Z (visão frontal)
            // Nesta vista, o eixo X é o que aponta para a direita/esquerda na tela.
            // O eixo Y é o que aponta para cima/baixo na tela.
            // O eixo Z do mundo aponta para dentro/fora da tela (profundidade).
            // Para movimento intuitivo, Cima/Baixo devem mover em X, Esquerda/Direita devem mover em Z.
            switch(key) {
                case GLUT_KEY_UP: // "Para cima" na tela (em X positivo, pinguim se afastando)
                    newZ -= step;
                    penguimRotationAngle = 180.0; // Pinguim olhando para Z negativo
                    direcaoAtualPinguim = FACING_BACKWARD;
                    break;
                case GLUT_KEY_DOWN: // "Para baixo" na tela (em X negativo, pinguim se aproximando)
                    newZ += step;
                    penguimRotationAngle = 0.0; // Pinguim olhando para Z positivo
                    direcaoAtualPinguim = FACING_FORWARD;
                    break;
                case GLUT_KEY_LEFT: // "Para a esquerda" na tela (em Z negativo)
                    newX -= step;
                    penguimRotationAngle = -90.0; // Pinguim olhando para X negativo
                    direcaoAtualPinguim = FACING_RIGHT; // Pinguim vira para a "direita"
                    break;
                case GLUT_KEY_RIGHT: // "Para a direita" na tela (em Z positivo)
                    newX += step;
                    penguimRotationAngle = 90.0; // Pinguim olhando para X positivo
                    direcaoAtualPinguim = FACING_LEFT; // Pinguim vira para a "esquerda"
                    break;
            }
            break;
        case 3: // Câmera Perspectiva (comportamento original)
        default:
            // Este comportamento já é relativo à direção do pinguim, o que é bom para a perspectiva.
            switch(key) {
                case GLUT_KEY_UP: // Seta para Cima
                    if (direcaoAtualPinguim == FACING_FORWARD) {
                        newZ += step;
                        movedOrChangedDirection = true;
                    } else {
                        direcaoAtualPinguim = FACING_FORWARD;
                        penguimRotationAngle = 0.0;
                    }
                    break;
                case GLUT_KEY_DOWN: // Seta para Baixo
                    if (direcaoAtualPinguim == FACING_BACKWARD) {
                        newZ -= step;
                        movedOrChangedDirection = true;
                    } else {
                        direcaoAtualPinguim = FACING_BACKWARD;
                        penguimRotationAngle = 180.0;
                    }
                    break;
                case GLUT_KEY_LEFT: // Seta para Esquerda
                    if (direcaoAtualPinguim == FACING_LEFT) {
                        newX += step;
                        movedOrChangedDirection = true;
                    } else {
                        direcaoAtualPinguim = FACING_LEFT;
                        penguimRotationAngle = 90.0;
                    }
                    break;
                case GLUT_KEY_RIGHT: // Seta para Direita
                    if (direcaoAtualPinguim == FACING_RIGHT) {
                        newX -= step;
                        movedOrChangedDirection = true;
                    } else {
                        direcaoAtualPinguim = FACING_RIGHT;
                        penguimRotationAngle = -90.0;
                    }
                    break;
            }
            break;
    }
    // Não deixa mãe andar fora do gelo
    if (newX > (-ICE_SHEET_HALF_SIZE + PENGUIN_RADIUS) &&
        newX < (ICE_SHEET_HALF_SIZE - PENGUIN_RADIUS) &&
        newZ > (-ICE_SHEET_HALF_SIZE + PENGUIN_RADIUS) &&
        newZ < (ICE_SHEET_HALF_SIZE - PENGUIN_RADIUS)) {

        if (newX != motherPenguinX || newZ != motherPenguinZ) {
            motherPenguinX = newX;
            motherPenguinZ = newZ;
            movedOrChangedDirection = true;
        }
        // Verifica colisão com buracos após o movimento
        checkHoleCollisions();
    }

    if (movedOrChangedDirection) {
        lastKeyPressedTime = glutGet(GLUT_ELAPSED_TIME);
    }
    
    glutPostRedisplay();
}
