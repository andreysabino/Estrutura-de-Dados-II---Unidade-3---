# Projeto de Ordenação de Números

Este projeto implementa e compara vários algoritmos de ordenação em C. Ele gera números aleatórios, salva-os em um arquivo, e mede o tempo de execução de cada algoritmo para diferentes tamanhos de vetores.

## Alterações Realizadas

Foram feitas várias correções e melhorias no código para garantir que ele funcione corretamente e de forma eficiente. Abaixo estão as principais alterações:

### 1. **Correção de Vazamentos de Memória**
- Adicionados `free` para liberar toda a memória alocada dinamicamente.
- Verificações adicionais para garantir que a alocação de memória foi bem-sucedida antes de usar os ponteiros.

### 2. **Correção das Funções de Ordenação**
- **BubbleSort:** Corrigido para evitar recursão desnecessária e acesso fora dos limites do array.
- **BucketSort:** Ajustado para lidar corretamente com valores maiores que o tamanho do vetor.
- **QuickSort e MergeSort:** Verificados e corrigidos para garantir que funcionem corretamente em todos os casos.
- **GnomeSort e ShellSort:** Implementações revisadas para garantir eficiência e corretude.

### 3. **Consistência no Uso de C**
- Removido o uso de `ofstream` (C++) e substituído por funções C (`fopen`, `fprintf`, etc.).
- Garantida a consistência no uso de bibliotecas e funções.

### 4. **Verificações de Erro**
- Adicionadas verificações para garantir que arquivos sejam abertos corretamente.
- Verificações para garantir que a alocação de memória não falhe.

### 5. **Melhoria na Legibilidade e Organização**
- Código reorganizado para facilitar a leitura e manutenção.
- Comentários adicionados para explicar trechos complexos.

### 6. **Geração de Números Aleatórios**
- A função `gerarNumerosAleatorios` foi corrigida para salvar os números gerados em um arquivo (`numerosAleatorios.txt`).
- Adicionada semente fixa (`srand(100)`) para garantir reproducibilidade.

### 7. **Medição de Tempo**
- Adicionada função `tempo` para converter o tempo de `clock_t` para segundos.
- Tempos de execução de cada algoritmo são salvos no arquivo `tempos.txt`.

---

## Como Usar

### Compilação
Para compilar o projeto, use o seguinte comando:

```bash
gcc -o ordenacao ordenacao.c
```

## Execução
Execute o programa gerado:

```bash
./ordenacao
```
# Saída

O programa gera um arquivo `numerosAleatorios.txt` com os números aleatórios.
Os tempos de execução de cada algoritmo são salvos no arquivo `tempos.txt`.

## Estrutura do Código

### Funções Principais

* `numerosAleatorios`: Gera um vetor de números aleatórios.
* `lerDados`: Lê os números aleatórios do arquivo.
* `gerarNumerosAleatorios`: Gera números aleatórios e salva no arquivo.

### Algoritmos de Ordenação:

* `bubbleSort`
* `selectionSort`
* `quickSort`
* `mergeSort`
* `bucketSort`
* `gnomeSort`
* `shellSort`
* `mostrarValores`: Exibe os valores do vetor (usado para debug).
* `tempo`: Converte o tempo de `clock_t` para segundos.

## Arquivos Gerados

* `numerosAleatorios.txt`: Contém os números aleatórios gerados.
* `tempos.txt`: Contém os tempos de execução de cada algoritmo para diferentes tamanhos de vetores.

## Exemplo de Saída no `tempos.txt`

O arquivo `tempos.txt` terá o seguinte formato:

| Tamanho | BubbleSort | QuickSort | MergeSort | BucketSort | SelectionSort | GnomeSort | ShellSort |
|---------|------------|-----------|-----------|------------|---------------|-----------|-----------|
| 10      | 0.000123   | 0.000045  | 0.000056  | 0.000034   | 0.000078      | 0.000089  | 0.000067  |
| 20      | 0.000456   | 0.000123  | 0.000145  | 0.000098   | 0.000134      | 0.000156  | 0.000123  |

## Contribuições

Se você encontrar problemas ou tiver sugestões de melhorias, sinta-se à vontade para abrir uma *issue* ou enviar um *pull request*.

