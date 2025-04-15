import time
import os

def get_robos_templates():

    rt = [
        ['---[]---'], ['[]------'], ['------[]'],
        ['[M2]----'], ['[M3]----'],
        ['[o]-----'], ['-----[o]']
    ]

    return rt

def get_maquinas_templates():

    mt = [
        ['[------]'], ['[o-----]'], ['[-->o--]'], ['[-----o]']
    ]

    return mt

def get_interacoes():

    rt = get_robos_templates()
    mt = get_maquinas_templates()

    interacoes = {
    'CIn: Item na Entrada, processando...\n': mt[2][0],
    'CIn: Item pronto na saida\n': mt[3][0],
    'R1: Movendo para CIn\n': rt[1][0],
    'R1: Retirando da CIn\n': rt[5][0],
    'R1: Movendo para M1\n': rt[6][0],
    'R1: Depositando em M1\n': rt[2][0],
    'M1: Item na Entrada, processando...\n': mt[2][0],
    'M1: Item pronto na saida\n': mt[3][0],
    'R2: Movendo para M1\n': rt[1][0],
    'R2: Retirando da M1\n': rt[5][0],
    'R2: Movendo para M2\n': rt[6][0],
    'R2: Depositando em M2\n': rt[2][0],
    'M2: Item na Entrada, processando...\n': mt[2][0],
    'M2: Item pronto na saida\n': mt[3][0],
    'R3: Movendo para M1\n': rt[1][0],
    'R3: Retirando da M1\n': rt[5][0],
    'R3: Movendo para M3\n': rt[6][0],
    'R3: Depositando em M3\n': rt[2][0],
    'M3: Item na Entrada, processando...\n': mt[2][0],
    'M3: Item pronto na saida\n': mt[3][0],
    'R4: Movendo para M2\n': rt[3][0],
    'R4: Retirando da M2\n': rt[5][0],
    'R4: Movendo para M3\n': rt[4][0],
    'R4: Retirando da M3\n': rt[5][0],
    'R4: Movendo para COut\n': rt[6][0],
    'R4: Depositando em COut\n': rt[2][0],
    'COut: Item na Entrada, processando...\n': mt[2][0],
    'COut: Item Entregue!\n': mt[0][0]
    }

    return interacoes

def print_estados(celin, r1, m1, r2, m2, r3, m3, r4, celout):

    print(f'                              R2    M2')
    print(f'CelIn       R1    M1       {r2} {m2}   R4    CelOut')
    print(f'{celin} {r1} {m1}                  {r4} {celout}')
    print(f'                           {r3} {m3}')
    print(f'                              R3    M3')

def main():

    with open("comandos.txt", encoding="utf-8") as f:
        comandos = f.readlines()
    
    rt = get_robos_templates()
    mt = get_maquinas_templates()
    interacoes = get_interacoes()

    celin = mt[0][0]
    r1 = rt[0][0]
    m1 = mt[0][0]
    r2 = rt[0][0]
    m2 = mt[0][0]
    r3 = rt[0][0]
    m3 = mt[0][0]
    r4 = rt[0][0]
    celout = mt[0][0]

    os.system('clear')
    for linha in comandos:
        label = linha[0:2]

        if label == 'CI': 
            celin = interacoes[linha]
        if label == 'R1': 
            r1 = interacoes[linha]
            if linha == 'R1: Depositando em M1\n':
                m1 = mt[1][0]
            elif linha == 'R1: Retirando da CIn\n':
                celin = mt[0][0]
        if label == 'M1': 
            m1 = interacoes[linha]
        if label == 'R2': 
            r2 = interacoes[linha]
            if linha == 'R2: Depositando em M2\n':
                m2 = mt[1][0]
            elif linha == 'R2: Retirando da M1\n':
                m1 = mt[0][0]
        if label == 'M2': 
            m2 = interacoes[linha]
        if label == 'R3': 
            r3 = interacoes[linha]
            if linha == 'R3: Depositando em M3\n':
                m3 = mt[1][0]
            elif linha == 'R3: Retirando da M1\n':
                m1 = mt[0][0]
        if label == 'M3': 
            m3 = interacoes[linha]
        if label == 'R4': 
            r4 = interacoes[linha]
            if linha == 'R4: Depositando em COut\n':
                celout = mt[1][0]
            elif linha == 'R4: Retirando da M2\n':
                m2 = mt[0][0]
            elif linha == 'R4: Retirando da M3\n':
                m3 = mt[0][0]
        if label == 'CO': 
            celout = interacoes[linha]
        
        print(linha)
        print_estados(celin, r1, m1, r2, m2, r3, m3, r4, celout)
        input("Pressione Enter para continuar...")
        os.system('clear')


if __name__ == '__main__':
    main()