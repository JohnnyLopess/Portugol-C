#!/bin/bash

SRC_DIR="src"
TEST_DIR="testes"
INPUT_DIR="$TEST_DIR/inputs"
EXPECTED_DIR="$TEST_DIR/expected"
BUILD_DIR="build"
OUTPUT_DIR="$BUILD_DIR/test_outputs"

# Garante que a pasta de saída exista
mkdir -p "$OUTPUT_DIR"

PASSOU=0
FALHOU=0

echo "Iniciando testes automatizados..."

for input in "$INPUT_DIR"/*.pg; do
    base=$(basename "$input" .pg)
    esperado="$EXPECTED_DIR/$base.expected"
    out_file="$OUTPUT_DIR/$base.c"

    echo "🔹 Testando $base..."

    # Limpa qualquer saída anterior
    rm -f $BUILD_DIR/saida.c

    # Executa o compilador
    make run FILE="$input" > /dev/null 2>&1

    # Verifica se o arquivo foi gerado no diretório build
    if [ ! -f $BUILD_DIR/saida.c ]; then
        echo "❌ $base falhou: saida.c não foi gerado"
        FALHOU=$((FALHOU+1))
        continue
    fi

    # Copia a saída do compilador para a pasta de teste
    cp $BUILD_DIR/saida.c "$out_file"

    if diff -q "$out_file" "$esperado" > /dev/null; then
        echo "✅ $base passou"
        PASSOU=$((PASSOU+1))
    else
        echo "❌ $base falhou"
        echo "🔍 Diferença:"
        diff -u "$out_file" "$esperado"
        FALHOU=$((FALHOU+1))
    fi
done

echo ""
echo "✅ Passaram: $PASSOU"
echo "❌ Falharam: $FALHOU"

exit $FALHOU