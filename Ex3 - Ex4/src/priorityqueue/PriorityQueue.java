package priorityqueue;

import java.util.*;

public class PriorityQueue<E> implements AbstractQueue<E> {
	/*
	 * Comparator<? super E> comparator: Un comparatore che determina l'ordinamento
	 * degli elementi nella coda di priorità.
	 * List<E> queue: Una lista che rappresenta effettivamente la coda di priorità.
	 * Map<E, Integer> map: Una mappa che tiene traccia della posizione di ciascun
	 * elemento all'interno della coda,
	 * per consentire operazioni efficienti come la ricerca e la rimozione.
	 */
	Comparator<? super E> comparator = null;
	List<E> queue;
	Map<E, Integer> map;

	/*
	 * Il costruttore inizializza la coda di priorità con un comparatore
	 * specificato.
	 * Se il comparatore è nullo, viene lanciata un'eccezione
	 * PriorityQueueException.
	 */
	public PriorityQueue(Comparator<? super E> comparator) throws PriorityQueueException {
		if (comparator == null)
			throw new PriorityQueueException("PriorityQueue: comparator cannot be null");
		this.comparator = comparator;
		this.queue = new ArrayList<>();
		this.map = new HashMap<>();
	}

	/*
	 * Verifica se la coda di priorità è vuota.
	 * Complessità: O(1)
	 */
	public boolean empty() {
		return queue.isEmpty();
	}

	// aggiunge un elemento alla coda -- O(logN)
	public boolean push(E e) {
		if (map.containsKey(e)) {
			return false;
		}
		queue.add(e);
		map.put(e, queue.size() - 1);
		siftUp(queue.size() - 1);
		return true;
	}

	// controlla se un elemento è in coda -- O(1)
	public boolean contains(E e) {
		if (e == null) {
			throw new PriorityQueueException("containsElement: element parameter cannot be null");
		}
		return map.containsKey(e);
	}

	// siftUp(int i): Esegue l'operazione di "sifting up" nell'queue dopo
	// l'inserimento
	// di un elemento per mantenere l'ordine della coda di priorità.
	private void siftUp(int i) {
		E target = queue.get(i);
		int parentIndex = (i - 1) / 2;
		while (i > 0 && comparator.compare(target, queue.get(parentIndex)) < 0) {
			queue.set(i, queue.get(parentIndex));
			map.put(queue.get(i), i);
			i = parentIndex;
			parentIndex = (i - 1) / 2;
		}
		queue.set(i, target);
		map.put(target, i);
	}

	// siftDown(int i): Esegue l'operazione di "sifting down" nella queue dopo la
	// rimozione
	// di un elemento per mantenere l'ordine della coda di priorità.
	private void siftDown(int i) {
		E target = queue.get(i);
		int childIndex = 2 * i + 1;
		while (childIndex < queue.size()) {
			if (childIndex + 1 < queue.size()
					&& comparator.compare(queue.get(childIndex + 1), queue.get(childIndex)) < 0) {
				childIndex++;
			}
			if (comparator.compare(target, queue.get(childIndex)) <= 0) {
				break;
			}
			queue.set(i, queue.get(childIndex));
			map.put(queue.get(i), i);
			i = childIndex;
			childIndex = 2 * i + 1;
		}
		queue.set(i, target);
		map.put(target, i);
	}

	// accede all'elemento in cima alla coda -- O(1)
	public E top() {
		if (empty()) {
			throw new PriorityQueueException("top: non posso prelevare un elemento da una coda vuota");
		}
		return queue.get(0);
	}

	// rimuove l'elemento in cima alla coda -- O(logN)
	public void pop() {
		if (empty()) {
			throw new PriorityQueueException("pop: non posso rimuovere elementi da una coda vuota");
		}

		E ultimo_elemento = queue.remove(queue.size() - 1);
		map.remove(ultimo_elemento);
		if (!queue.isEmpty()) {
			E elemento_mosso = queue.set(0, ultimo_elemento);
			map.put(elemento_mosso, 0);
			siftDown(0);
		}
	}

	// rimuove un elemento se presente in coda -- O(logN)
	public boolean remove(E e) {
		if (e == null) {
			throw new PriorityQueueException("removeElement: il parametro non può essere null");
		}

		Integer indice = map.remove(e);
		if (indice != null) {
			E ultimoelemento = queue.remove(queue.size() - 1);
			if (indice < queue.size()) {
				E muovielemento = queue.set(indice, ultimoelemento);
				map.put(muovielemento, indice);
				siftDown(indice);
				siftUp(indice);
			}
			return true;
		}
		return false;
	}

	// Aggiunge tutti gli elementi della collezione specificata alla coda di
	// priorità utilizzando il metodo push(E e).
	public void addAll(Collection<? extends E> collection) {
		for (E e : collection) {
			push(e);
		}
	}

}