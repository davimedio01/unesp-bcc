__author__ = "Shubham Sharma"

import networkx as nx
import matplotlib.pyplot as plt
from prettytable import PrettyTable


def menu():

    print("Following will be printed in order for the given schedule: ")
    print()
    print("1. Print schedule chart")
    print("2. Check if the given schedule is serial")
    print("3. Check if the given schedule is conflict serializable")
    print("4. Check if the given schedule is view serializable")
    print()


def txn_print(*txns):

    txn = PrettyTable()
    txn.field_names = [f"T{i + 1}" for i in range(len(txns))]

    for i in range(len(txns[0])):
        data = list()
        for j in range(len(txns)):
            data.append(txns[j][i])
        txn.add_row(data)

    print(txn)


def txn_value():
    txn_num = 0
    txns = list()
    actions = list()
    data_items = list()

    while txn_num == 0:

        txn_num = int(input("Enter number of transactions: "))

        if txn_num == 0:
            print()
            print("C'mon! Stop fooling around, Enter a non-zero value.")
            print()
            continue

        for _ in range(txn_num):
            txns.append(list())
            actions.append(list())
            data_items.append(list())

    while 1:

        choice = input("\nEnter transaction number as T1, T2,... or Q/q to exit: ")

        if choice.lower() == 'q':
            break

        if choice[0].lower != 't' and int(choice[1]) > txn_num and len(choice) > 2:
            print()
            print("Transaction doesn't exist, try again!")
            print()
            continue

        action = input(f"\nEnter action Read(R/r) or Write(W/w) for {choice.upper()}: ").upper()

        if action.lower() != 'r' and action.lower() != 'w':
            print()
            print("You can't do that here!\nStart over!!!")
            print()
            continue

        print()
        data_item = input(f"Enter any english letter as data_item for the {action}: ").upper()

        if not data_item.isalpha():
            print()
            print("Invalid input.\nStart over!!!")
            print()
            continue

        actions[int(choice[1]) - 1].append(action)
        data_items[int(choice[1]) - 1].append(data_item)
        txns[int(choice[1]) - 1].append(action + f"({data_item})")

        for i in range(txn_num):
            if int(choice[1]) - 1 != i:
                actions[i].append("*")
                data_items[i].append("*")
                txns[i].append("*")
        txn_print(*txns)

    return txns


def txn_serial_check(*txns):

    graph = nx.DiGraph()
    order = list()
    error = 0

    for i in range(len(txns[0])):
        for j in range(len(txns)):
            if txns[j][i] != "*":
                if not order:
                    order.append(f"T{j + 1}")
                else:
                    if f"T{j + 1}" in order:
                        if order[-1] == f"T{j + 1}":
                            pass
                        else:
                            order.append(f"T{j + 1}")
                            error = 1
                    else:
                        order.append(f"T{j + 1}")

    nodes = [f"T{i + 1}" for i in range(len(txns))]
    graph.add_nodes_from(nodes)
    edges = [(order[i], order[i + 1]) for i in range(len(order) - 1)]
    graph.add_edges_from(edges)

    try:
        nx.planar_layout(graph)
    except nx.exception.NetworkXException:
        pass

    if not error:
        print("The given schedule is serial schedule ")
        print()
        plt.title("Serial Schedule", fontsize=10, color="red")
        nx.draw(graph, with_labels=True, node_size=1500, font_size=20, font_color="yellow", font_weight="bold", connectionstyle='arc3, rad = 0.1')
        plt.show()
    else:
        print("The given schedule is not a serial schedule.")
        print()
        plt.title("NOT a Serial Schedule", fontsize=10, color="red")
        nx.draw(graph, with_labels=True, node_size=1500, font_size=20, font_color="yellow", font_weight="bold", connectionstyle='arc3, rad = 0.1')
        plt.show()


def blind_write(dataset, *txns):

    for d in dataset:
        for i in range(len(txns)):
            read_check = 0
            for j in range(len(txns[0])):
                if txns[i][j] == "*":
                    continue
                if txns[i][j][2] == d:
                    if txns[i][j][0] == "R":
                        read_check = 1
                    if txns[i][j][0] == "W":
                        if read_check == 0:
                            return 1
                        else:
                            break

    return 0


def txn_conflict_serial(*txns):

    edges = list()
    for i in range(len(txns)):
        flag = 0
        for j in range(len(txns[0])):
            if flag:
                break
            if txns[i][j] != "*":
                if txns[i][j][0] == "W":
                    for m in range(len(txns)):
                        if m == i:
                            continue
                        for n in range(j + 1, len(txns[0])):
                            if txns[m][n] == "*":
                                continue
                            if txns[i][j][2] == txns[m][n][2]:
                                if (f"T{i + 1}", f"T{m + 1}") not in edges:
                                    edges.append((f"T{i + 1}", f"T{m + 1}"))
                                flag = 1
                                break
                if txns[i][j][0] == "R":
                    for m in range(len(txns)):
                        if m == i:
                            continue
                        for n in range(j + 1, len(txns[0])):
                            if txns[m][n] == "*" or txns[m][n][0] == "R":
                                continue
                            if txns[i][j][2] == txns[m][n][2]:
                                if (f"T{i + 1}", f"T{m + 1}") not in edges:
                                    edges.append((f"T{i + 1}", f"T{m + 1}"))
                                flag = 1
                                break

    graph = nx.DiGraph()
    graph.add_nodes_from([f"T{i + 1}" for i in range(len(txns))])
    graph.add_edges_from(edges)

    try:
        nx.planar_layout(graph)
    except nx.exception.NetworkXException:
        pass

    try:
        nx.find_cycle(graph)
        plt.title("Not Conflict Serializable", fontsize=10, color="red")
        print("This schedule is not Conflict Serializable.")
        print()
        nx.draw(graph, with_labels=True, node_size=1500, font_size=20, font_color="yellow", font_weight="bold", connectionstyle='arc3, rad = 0.1')
        plt.show()
        return 1, graph
    except nx.exception.NetworkXNoCycle:
        plt.title(f"Conflict Serializable: <{','.join(nx.topological_sort(graph))}>", fontsize=10, color="red")
        print(f"This schedule is Conflict Serializable and Conflict Equivalent to <{','.join(nx.topological_sort(graph))}>")
        print()
        nx.draw(graph, with_labels=True, node_size=1500, font_size=20, font_color="yellow", font_weight="bold", connectionstyle='arc3, rad = 0.1')
        plt.show()
        return 0, ""


def txn_view_serial(conflict_status, graph_status, *txns):

    dataset = set([txns[i][j][2] for i in range(len(txns)) for j in range(len(txns[0])) if txns[i][j] != "*"])
    edges = list()

    for d in dataset:
        update_list = list()
        first_reads = list()
        last_update = ""
        for i in range(len(txns[0])):
            for j in range(len(txns)):
                if txns[j][i] == "*":
                    continue
                if txns[j][i][2] == d:
                    if txns[j][i][0] == "W":
                        update_list.append(f"T{j + 1}")
                        last_update = f"T{j + 1}"
                    if txns[j][i][0] == "R":
                        if not last_update:
                            first_reads.append(f"T{j + 1}")
                        else:
                            edges.append((last_update, f"T{j + 1}"))

        update_list_read = list(set(update_list) - set(first_reads))
        update_list = list(set(update_list))

        if first_reads:
            edges.extend([(x, y) for x in first_reads for y in update_list_read if x != y])
        if last_update:
            edges.extend([(x, last_update) for x in update_list if x != last_update])

    edges = [(e[0], e[1]) for e in edges if e[0] != e[1]]
    edges = list(set(edges))
    graph = nx.DiGraph()
    graph.add_nodes_from([f"T{x + 1}" for x in range(len(txns))])
    graph.add_edges_from(edges)

    if conflict_status and not blind_write(dataset, *txns):
        graph.clear()
        print("There is no Blind Write!")
        graph = graph_status

    try:
        nx.planar_layout(graph)
    except nx.exception.NetworkXException:
        pass

    try:
        nx.find_cycle(graph)
        plt.title("Not View Serializable", fontsize=10, color="red")
        print("This schedule is not View Serializable.")
        print()
        nx.draw(graph, with_labels=True, node_size=1500, font_size=20, font_color="yellow", font_weight="bold", connectionstyle='arc3, rad = 0.1')
    except nx.exception.NetworkXNoCycle:
        plt.title(f"View Serializable: <{','.join(nx.topological_sort(graph))}>", fontsize=10, color="red")
        print(f"This schedule is View Serializable and View Equivalent to <{','.join(nx.topological_sort(graph))}>")
        print()
        nx.draw(graph, with_labels=True, node_size=1500, font_size=20, font_color="yellow", font_weight="bold", connectionstyle='arc3, rad = 0.1')

    plt.show()


if __name__ == "__main__":
    while 1:
        menu()
        sel = input("Enter any key to continue or X to exit: ").lower()
        if sel == 'x':
            break
        print("Please follow the instructions to enter your values for schedule.\n")
        schedule = txn_value()

        txn_print(*schedule)

        txn_serial_check(*schedule)

        conflict = txn_conflict_serial(*schedule)

        txn_view_serial(conflict[0], conflict[1], *schedule)

    print("Thanks!!!")
