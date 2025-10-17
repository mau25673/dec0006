#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    public:
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada(){
        Elemento<T>* elementoProximo;
        for (Elemento<T>* elementoAtual = this->_primeiro; elementoAtual != nullptr; elementoAtual = elementoProximo){
            elementoProximo = elementoAtual->proximo;
            delete elementoAtual;
        }
        this->_primeiro = nullptr;
        this->_tamanho = 0;
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        return this->_tamanho;
    };
    
    /**
     * @brief Indica se há algum item na lista ou não.
     * 
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const 
    {
        return !(this->tamanho());
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const 
    {   
        if (this->vazia()){
            throw ExcecaoListaEncadeadaVazia();
        }
        size_t posicao = 0;
        for (Elemento<T>* i = this->_primeiro; i != nullptr; i = i->proximo, posicao++){
            if (i->dado == dado){
                return posicao;
            }
        }
        throw ExcecaoDadoInexistente();
    };
    
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        for (Elemento<T>* i = this->_primeiro; i != nullptr; i = i->proximo){
            if (i->dado == dado){
                return true;
            }
        }
        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado) 
    {
        this->_primeiro = new Elemento(dado, this->_primeiro);
        this->_tamanho++;
    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {
        if (posicao > this->tamanho()){
            throw ExcecaoPosicaoInvalida();
        }
        if (posicao == 0){
            this->inserirNoInicio(dado);
        }
        else{
            size_t posicao_atual = 0;
            Elemento<T> *novoElemento;
            for (Elemento<T>* i = this->_primeiro; i != nullptr; i = i->proximo, posicao_atual++){
                if(posicao_atual == posicao-1){
                    novoElemento = new Elemento(dado, i->proximo);
                    i->proximo = novoElemento;
                    this->_tamanho++;
                    break;
                }
            }
        }
    };


    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        //escreva o algoritmo esperado
        if (this->_tamanho == 0){
            this->inserirNoInicio(dado);
        }
        else{
            size_t posicao_atual = 0;
            Elemento<T> *novoElemento;
            for (Elemento<T>* i = this->_primeiro; i != nullptr; i = i->proximo, posicao_atual++){
                if(posicao_atual == this->_tamanho-1){
                    novoElemento = new Elemento<T>(dado, nullptr);
                    i->proximo = novoElemento;
                    this->_tamanho++;
                    break;
                }
            }
        }
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        if(this->_primeiro == nullptr){
            throw ExcecaoListaEncadeadaVazia();
        }
        Elemento<T> *primeiroAnterior = this->_primeiro;
        this->_primeiro = this->_primeiro->proximo;
        T dadoAntigo = primeiroAnterior->dado;
        delete primeiroAnterior;
        this->_tamanho--;
        return dadoAntigo;
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        if(posicao >= this->tamanho()){
            throw ExcecaoPosicaoInvalida();
        }
        else if(posicao == 0){
            return this->removerDoInicio();
        }
        else if(this->tamanho()-1 == posicao){
            return this->removerDoFim();
        }
        else{
            size_t posicao_atual = 0;
            for (Elemento<T>* i = this->_primeiro; i != nullptr; i = i->proximo, posicao_atual++){
                if (posicao_atual == posicao-1){
                    Elemento<T>* antigoElemento = i->proximo;
                    T dadoAntigo = antigoElemento->dado;
                    i->proximo = antigoElemento->proximo;
                    delete antigoElemento;
                    this->_tamanho--;
                    return dadoAntigo;
                }
            }
        }
    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
        
        if(this->_primeiro == nullptr){
            throw ExcecaoListaEncadeadaVazia();
        }
        else if(this->_primeiro->proximo == nullptr){
            return this->removerDoInicio();
        }
        else{
            size_t posicao_atual = 0;
            for (Elemento<T>* i = this->_primeiro; i != nullptr; i = i->proximo, posicao_atual++){
                if (posicao_atual == this->_tamanho-2){
                    Elemento<T>* antigoUltimo = i->proximo;
                    T dadoAntigo = antigoUltimo->dado;
                    i->proximo = nullptr;
                    delete antigoUltimo;
                    this->_tamanho--;
                    return dadoAntigo;
                }
            }
        }
    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado)
    {
        if (this->tamanho() == 0){
            throw ExcecaoListaEncadeadaVazia();
        }
        if (!(this->contem(dado))){
            throw ExcecaoDadoInexistente();
        }
        if(this->_primeiro->dado == dado){
            this->removerDoInicio();
        }
        else{
            Elemento<T>* elementoAnterior = this->_primeiro;
            for (Elemento<T>* i = this->_primeiro->proximo; i != nullptr; i = i->proximo){
                if(i->dado == dado){
                    elementoAnterior->proximo = i->proximo;
                    delete i;
                    this->_tamanho--;
                    break;
                }
                elementoAnterior = elementoAnterior->proximo;
            }
        }
    };
};

#endif