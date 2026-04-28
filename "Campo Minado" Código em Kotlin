
fun criaMenu(): String{
    return "\nBem vindo ao Campo DEISIado\n" +
            "\n1 - Novo Jogo" +
            "\n2 - Ler Jogo" +
            "\n0 - Sair\n"
}

fun validaNome(nome: String, tamanhoMinimo: Int = 3): Boolean {
    var espacoContado = 0
    var tamanhoPalavraAtual = 0
    var tamanhoPrimeiraPalavra = 0
    var inicioDaPalavra = true

    var posicao = 0

    while (posicao < nome.length) {
        val caractere = nome[posicao]

        if (caractere == ' ') {
            espacoContado++
            if (espacoContado > 1) return false
            tamanhoPrimeiraPalavra = tamanhoPalavraAtual
            tamanhoPalavraAtual = 0
            inicioDaPalavra = true
        } else {
            if (inicioDaPalavra) {
                if (caractere !in 'A'..'Z') return false
                inicioDaPalavra = false
            } else {
                if (caractere !in 'a'..'z') return false
            }
            tamanhoPalavraAtual++
        }
        posicao++
    }

    val tamanhoSegundaPalavra = tamanhoPalavraAtual

    if (espacoContado != 1) return false
    if (tamanhoPrimeiraPalavra < tamanhoMinimo) return false
    if (tamanhoSegundaPalavra < tamanhoMinimo) return false

    return true
}

fun criaLegenda(colunas: Int): String {
    var legenda = ""
    var posicao = 0

    while (posicao < colunas) {
        val letra = 'A' + posicao
        legenda += letra
        if (posicao < colunas - 1) legenda += "   "
        posicao++
    }
    return legenda
}

fun validaNumeroDeMinas(linhas: Int, colunas: Int, numMinas: Int): Boolean {
    if (linhas < 1 || colunas < 3 || numMinas <= 0) return false

    val espacosLivres = (colunas - 2) * linhas
    return numMinas <= espacosLivres
}

fun calculaNumeroDeMinas(linhas: Int, colunas: Int): Int {
    val espacosLivres = (colunas - 2) * linhas

    return when (espacosLivres) {
        1 -> 1
        in 2..5 -> 2
        in 6..10 -> 3
        in 11..20 -> 6
        in 21..50 -> 10
        else -> 15
    }
}

fun obtemCoordenadas(coordenadas: String?): Pair<Int,Int>? {
    if (coordenadas==null || coordenadas.length != 2) {
        return null
    }

    val linhachar = coordenadas[0]
    val colunachar = coordenadas[1]

    if (!linhachar.isDigit() || !colunachar.isLetter()) {
        return null
    }

    val linha = linhachar.digitToInt() - 1
    val coluna = colunachar.uppercaseChar().code - 'A'.code

    if (linha < 0 || linha > 7 || coluna < 0 || coluna > 7) {
        return null
    }

    return Pair(linha, coluna)
}


fun validaCoordenadasDentroTerreno(par: Pair<Int, Int>, numLinhas: Int, numColunas: Int): Boolean {
    val linha = par.first
    val coluna = par.second
    if (linha >= 0 && linha < numLinhas && coluna >= 0 && coluna < numColunas) {
        return true
    }
    return false
}

fun validaMovimentoJogador(parOrigem: Pair<Int, Int>, parDestino: Pair<Int, Int>): Boolean {

    val diferencaLinha = kotlin.math.abs(parDestino.first - parOrigem.first)
    val diferencaColuna = kotlin.math.abs(parDestino.second - parOrigem.second)

    if (diferencaLinha  == 0 && diferencaColuna == 0) return false

    return diferencaLinha <= 2 && diferencaColuna <= 2
}

fun quadradoAVoltaDoPonto(linha: Int, coluna: Int, numLinhas: Int , numColunas: Int): Pair<Pair<Int, Int>, Pair<Int, Int>> {

    val linhaInicialQuadrado = maxOf(0, linha - 1)
    val colunaInicialQuadrado = maxOf(0, coluna - 1)

    val linhaFinalQuadrado = minOf(numLinhas - 1, linha + 1)
    val colunaFinalQuadrado = minOf(numColunas - 1, coluna + 1)

    return Pair(Pair(linhaInicialQuadrado, colunaInicialQuadrado), Pair(linhaFinalQuadrado, colunaFinalQuadrado))
}

fun contaMinasPerto(v1: Array<Array<Pair<String, Boolean>>>, linha: Int, coluna: Int): Int {

    val numLinhas = v1.size
    val numColunas = v1[0].size

    val (inicio, fim) = quadradoAVoltaDoPonto(linha, coluna, numLinhas, numColunas)
    val (linhaInicial, colunaInicial) = inicio
    val (linhaFinal, colunaFinal) = fim

    var contador = 0
    for (i in linhaInicial..linhaFinal) {
        for (j in colunaInicial..colunaFinal) {
            if (i != linha || j != coluna) {
                if (v1[i][j].first == "*") {
                    contador++
                }
            }
        }
    }
    return contador
}

fun geraMatrizTerreno(numLinhas: Int, numColunas: Int, numMinas: Int): Array<Array<Pair<String, Boolean>>> {

    val terreno = Array(numLinhas) {
        Array(numColunas) { Pair(" ", false) }
    }

    terreno[0][0] = Pair("J", true)

    terreno[numLinhas - 1][numColunas - 1] = Pair("f", true)

    var quantidadeDeMinasColocadas = 0
    val maximoDeMinasPossiveis = numLinhas * numColunas - 2
    val totalDeMinasAColocar = minOf(numMinas, maximoDeMinasPossiveis)

    while (quantidadeDeMinasColocadas < totalDeMinasAColocar) {
        val indiceLinhaAleatoria = Random.nextInt(numLinhas)
        val indiceColunaAleatoria = Random.nextInt(numColunas)
        val estaNaPosicaoInicialJogador = indiceLinhaAleatoria == 0 && indiceColunaAleatoria == 0
        val estaNaPosicaoFinalObjetivo = indiceLinhaAleatoria == numLinhas - 1 && indiceColunaAleatoria == numColunas - 1
        val jaExisteMinaNestaPosicao = terreno[indiceLinhaAleatoria][indiceColunaAleatoria].first == "*"

        val podeColocarMina = !estaNaPosicaoInicialJogador && !estaNaPosicaoFinalObjetivo && !jaExisteMinaNestaPosicao

        if (podeColocarMina) {
            terreno[indiceLinhaAleatoria][indiceColunaAleatoria] = Pair("*", false)
            quantidadeDeMinasColocadas++
        }
    }

    return terreno
}

fun preencheNumMinasNoTerreno(terreno: Array<Array<Pair<String, Boolean>>>) {
    val numeroDeLinhas = terreno.size
    val numeroDeColunas = terreno[0].size

    for (linha in 0 until numeroDeLinhas) {
        for (coluna in 0 until numeroDeColunas) {

            val valorAtual = terreno[linha][coluna].first

            val ehMina = valorAtual == "*"
            val ehInicio = valorAtual == "J"
            val ehFim = valorAtual == "f"

            if (!ehMina && !ehInicio && !ehFim) {
                val numMinasPorPerto = contaMinasPerto(terreno, linha, coluna)

                if (numMinasPorPerto > 0) {
                    terreno[linha][coluna] = Pair(numMinasPorPerto.toString(), false)
                } else {
                    terreno[linha][coluna] = Pair(" ", true)
                }
            }
        }
    }
}


fun revelaMatriz(v1: Array<Array<Pair<String, Boolean>>>, linha: Int, coluna: Int) {
    val numLinhas = v1.size
    val numColunas = v1[0].size

    val (inicio, fim) = quadradoAVoltaDoPonto(linha, coluna, numLinhas, numColunas)
    val (linhaInicial, colunaInicial) = inicio
    val (linhaFinal, colunaFinal) = fim

    for (l in linhaInicial..linhaFinal) {
        for (c in colunaInicial..colunaFinal) {
            val (valor, revelada) = v1[l][c]
            if (!revelada && valor != "*" && valor != "J") {
                v1[l][c] = Pair(valor, true)
            }
        }
    }
}

fun celulaTemNumeroMinasVisivel(v1: Array<Array<Pair<String, Boolean>>>, linha: Int, coluna: Int): Boolean {
    val celula= v1[linha][coluna]

    val valor= celula.first
    val visivel= celula.second

    if (!visivel || valor.length!=1 || !valor[0].isDigit()){
        return false
    }
    return true
}

fun escondeMatriz(v1: Array<Array<Pair<String, Boolean>>>) {
    for (linha in v1.indices) {
        for (coluna in v1[linha].indices) {

            val valor= v1[linha][coluna].first
            val visivel: Boolean
            if (valor=="J" || valor=="f"){
                visivel=true

            }else{
                visivel= false
            }

            v1[linha][coluna]= Pair(valor,visivel)
        }
    }
}


fun validaTerreno(v1: Array<Array<Pair<String, Boolean>>>): Boolean {
    if (v1.isEmpty() || v1[0].isEmpty()) return false

    val numLinhas = v1.size
    val numColunas = v1[0].size
    var jogadorEncontrado = false
    var finalEncontrado = false

    for (linha in v1.indices) {
        if (v1[linha].size != numColunas) return false

        for (coluna in v1[linha].indices) {
            val valor = v1[linha][coluna].first

            when (valor) {
                "J" -> {
                    if (jogadorEncontrado) return false
                    jogadorEncontrado = true
                }
                "f" -> {
                    if (finalEncontrado) return false
                    finalEncontrado = true
                }
                "*", " " -> {
                }
                else -> {
                    if (!valor.matches(Regex("\\d+"))) return false
                }
            }
        }
    }

    if (!jogadorEncontrado || !finalEncontrado) return false

    if (v1[0][0].first != "J") return false

    if (v1[numLinhas - 1][numColunas - 1].first != "f") return false

    return true
}

fun criaTerreno(matriz: Array<Array<Pair<String, Boolean>>>, mostraLegenda: Boolean, mostraTudo: Boolean): String {

    var terreno = ""

    if (mostraLegenda) {
        terreno += "    " + criaLegenda(matriz[0].size) + "    \n"
    }

    var contadorLinha = 0
    for (linha in matriz) {

        if (mostraLegenda) {
            terreno += " ${contadorLinha + 1}  "   // ← 2 espaços no fim
        }

        var contadorColuna = 0
        for (celula in linha) {

            val simbolo = celula.first
            val visivel = celula.second

            val aMostrar = if (visivel || mostraTudo) simbolo else " "

            terreno += aMostrar

            if (contadorColuna < linha.size - 1) {
                terreno += " | "
            }

            contadorColuna++
        }

        terreno += if (mostraLegenda) "    " else " "

        if (contadorLinha < matriz.size - 1) {
            terreno += "\n"

            if (mostraLegenda) {
                terreno += "   "
            }

            contadorColuna = 0
            for (i in linha.indices) {
                terreno += "---"
                if (i < linha.size - 1) {
                    terreno += "+"
                }
            }

            terreno += if (mostraLegenda) "   \n" else "\n"

        } else if (mostraLegenda) {
            terreno += "\n"
        }

        contadorLinha++
    }

    return terreno
}

fun lerFicheiroJogo(nomeFicheiro: String, numLinhas: Int, numColunas: Int): Array<Array<Pair<String, Boolean>>>? {
    if (nomeFicheiro == "") return null
    return arrayOf(arrayOf(Pair(" ",false)))
}

fun naada() {
    println("Resposta invalida.")
}

fun pedirNome(): String {
    var nome: String
    while (true) {
        println("Introduz o nome do jogador")
        nome = readln()
        if (!validaNome(nome)) {
            naada()
        } else {
            return nome
        }
    }
}

fun escolherLegenda(): Boolean {
    var legenda = ""
    while (legenda != "s" && legenda != "n") {
        println("Mostrar legenda (s/n)?")
        legenda = readln()
        if (!(legenda == "s" || legenda == "n")) {
            naada()
        } else if (legenda == "s") {
            return true
        } else {
            return false
        }
    }
    return false
}

fun pedirLinhas(): Int {
    var linhas = 0
    while (true) {
        println("Quantas linhas?")
        val input = readln()
        linhas = input.toIntOrNull() ?: -1
        if (linhas >= 1) {
            return linhas
        } else {
            naada()
        }
    }
}

fun pedirColunas(): Int {
    val colunas = 0
    while (true) {
        println("Quantas colunas?")
        val colunas = readln().toIntOrNull() ?: -1
        if (colunas in 1..26) {
            return colunas
        } else {
            naada()
        }
    }
}


fun criaTabuleiro(): Array<Array<Pair<String, Boolean>>> {
    val plinhas = pedirLinhas()
    val pcolunas = pedirColunas()

    println("Quantas minas (ou enter para o valor por omissao)?")
    val escminas = readln()
    val minas = if (escminas == "") {
        calculaNumeroDeMinas(plinhas, pcolunas)
    } else {
        val numMinas = escminas.toIntOrNull() ?: -1
        if (validaNumeroDeMinas(plinhas, pcolunas, numMinas)) {
            numMinas
        } else {
            naada()
            calculaNumeroDeMinas(plinhas, pcolunas)
        }

    }

    val tabuleiro = geraMatrizTerreno(plinhas, pcolunas, minas)

    preencheNumMinasNoTerreno(tabuleiro)

    return tabuleiro
}


fun movimentoJogador(tabuleiro: Array<Array<Pair<String, Boolean>>>): Pair<Int, Int>? {

    while (true) {

        println("Introduz a celula destino (ex: 2D)")

        val pedeCoordenadas = readlnOrNull()

        if (pedeCoordenadas == "sair") {

            return Pair(-1, -1)

        } else if (pedeCoordenadas == "abracadabra") {

            println(criaTerreno(tabuleiro, true, true))

        } else {

            val coordenadas = obtemCoordenadas(pedeCoordenadas)

            if (coordenadas == null) {

                return null

            } else {
                return coordenadas
            }

        }
    }

}


fun confirmaMovimento(tabuleiro: Array<Array<Pair<String, Boolean>>>, origem: Pair<Int, Int>): Pair<Int, Int>? {

    var destino = Pair(0, 0)

    val coordsValidas = movimentoJogador(tabuleiro)
    if (coordsValidas == null) {

        return null

    } else {

        if (coordsValidas == Pair(-1, -1)) {

            return Pair(-1, -1)

        }
        if (!(validaCoordenadasDentroTerreno(coordsValidas, tabuleiro.size, tabuleiro[0].size))) {

            return null

        } else if (!validaMovimentoJogador(origem, coordsValidas)) {

            return null

        } else {

            destino = coordsValidas

        }
    }

    return destino
}

fun jogoSemLegenda(tabuleiro: Array<Array<Pair<String, Boolean>>>): Boolean {

    var jogador = Pair(0, 0)

    var gameOn = true

    if (!(validaTerreno(tabuleiro))) {
        gameOn = false

    }

    revelaMatriz(tabuleiro, jogador.first, jogador.second)

    while (gameOn) {

        println(criaTerreno(tabuleiro, false, false))

        val destino = confirmaMovimento(tabuleiro, jogador)

        if (destino == Pair(-1, -1)) {

            return true

        } else if (destino == null) {

            println("Movimento invalido.")

        } else {

            tabuleiro[jogador.first][jogador.second] = Pair(" ", tabuleiro[jogador.first][jogador.second].second)

            val conteudo = tabuleiro[destino.first][destino.second].first

            escondeMatriz(tabuleiro)

            revelaMatriz(tabuleiro, destino.first, destino.second)

            tabuleiro[destino.first][destino.second] = Pair("J", true)

            jogador = destino

            if (conteudo == "*") {
                println("Perdeste o jogo!")
                revelaMatriz(tabuleiro, jogador.first, jogador.second)
                println(criaTerreno(tabuleiro, true, true))
                gameOn = false

            } else if (conteudo == "f") {
                println("ganhaste!")
                revelaMatriz(tabuleiro, jogador.first, jogador.second)
                println(criaTerreno(tabuleiro, true, true))
                gameOn = false
            }
        }
    }
    return false
}

fun jogoComLegenda(tabuleiro: Array<Array<Pair<String, Boolean>>>): Boolean {

    var jogador = Pair(0, 0)

    var gameOn = true

    if (!(validaTerreno(tabuleiro))) {
        gameOn = false

    }

    revelaMatriz(tabuleiro, jogador.first, jogador.second)

    while (gameOn) {

        println(criaTerreno(tabuleiro, true , false))

        val destino = confirmaMovimento(tabuleiro, jogador)

        if (destino == Pair(-1, -1)) {

            return true

        } else if (destino == null) {

            println("Movimento invalido.")

        } else {

            tabuleiro[jogador.first][jogador.second] = Pair(" ", tabuleiro[jogador.first][jogador.second].second)

            val conteudo = tabuleiro[destino.first][destino.second].first

            escondeMatriz(tabuleiro)

            revelaMatriz(tabuleiro, destino.first, destino.second)

            tabuleiro[destino.first][destino.second] = Pair("J", true)

            jogador = destino

            if (conteudo == "*") {
                println("Perdeste o jogo!")
                revelaMatriz(tabuleiro, jogador.first, jogador.second)
                println(criaTerreno(tabuleiro, true, true))
                gameOn = false

            } else if (conteudo == "f") {
                println("ganhaste!")
                revelaMatriz(tabuleiro, jogador.first, jogador.second)
                println(criaTerreno(tabuleiro, true, true))
                gameOn = false
            }
        }
    }
    return false
}

fun main() {

    var count = 0

    while (count == 0) {
        println(criaMenu())
        val menu = readln().toIntOrNull()
        if (menu == null || menu < 0 || menu > 2) {
            naada()
        } else if (menu == 2) {

            val nomeplyr = pedirNome()
            val legendas = escolherLegenda()


        } else if (menu == 0) {
            count++
        } else {

            val nomeplyr = pedirNome()
            val legendas = escolherLegenda()

            if (legendas) {
                val tabuleiroComl = criaTabuleiro()
                val jogoComl = jogoComLegenda(tabuleiroComl)
                if (jogoComl) {
                    count++
                }

            } else {
                val tabuleiroSeml = criaTabuleiro()

                val jogoSeml = jogoSemLegenda(tabuleiroSeml)
                if (jogoSeml) {
                    count++
                }
            }
        }
    }
}


