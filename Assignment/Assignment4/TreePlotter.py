"""
Filename: TreePlotter.py
Author: 郑鑫业 2023217265 计算机23-1
Note: This script is used to visualize a decision tree using matplotlib.
"""

import matplotlib.pyplot as plt

# 节点样式
decisionNode = dict(boxstyle="sawtooth", fc="0.8")
leafNode = dict(boxstyle="round4", fc="0.8")

# 箭头样式
arrow_args = dict(arrowstyle="<-")

def plot_node(node_txt, center_pt, parent_pt, node_type):
    """
    绘制一个节点
    :param node_txt: 描述该节点的文本信息
    :param center_pt: 文本的坐标
    :param parent_pt: 点的坐标，这里也是指父节点的坐标
    :param node_type: 节点类型,分为叶子节点和决策节点
    """
    create_plot.ax1.annotate(node_txt, xy=parent_pt, xycoords='axes fraction',
                            xytext=center_pt, textcoords='axes fraction',
                            va="center", ha="center", bbox=node_type, arrowprops=arrow_args)

def get_num_leafs(tree):
    """
    获取叶节点的数目
    :param tree: 决策树
    :return: 叶节点的数目
    """
    num_leafs = 0
    first_str = next(iter(tree))
    second_dict = tree[first_str]

    for key in second_dict:
        if isinstance(second_dict[key], dict):
            num_leafs += get_num_leafs(second_dict[key])
        else:
            num_leafs += 1
    return num_leafs

def get_tree_depth(tree):
    """
    得到树的深度层数
    :param tree: 决策树
    :return: 树的深度
    """
    max_depth = 0
    first_str = next(iter(tree))
    second_dict = tree[first_str]

    for key in second_dict:
        if isinstance(second_dict[key], dict):
            this_depth = 1 + get_tree_depth(second_dict[key])
        else:
            this_depth = 1
        max_depth = max(max_depth, this_depth)
    return max_depth

def plot_mid_text(cntr_pt, parent_pt, txt_string):
    """
    计算出父节点和子节点的中间位置，填充信息
    :param cntr_pt: 子节点坐标
    :param parent_pt: 父节点坐标
    :param txt_string: 填充的文本信息
    """
    x_mid = (parent_pt[0] - cntr_pt[0]) / 2.0 + cntr_pt[0]
    y_mid = (parent_pt[1] - cntr_pt[1]) / 2.0 + cntr_pt[1]
    create_plot.ax1.text(x_mid, y_mid, txt_string)

def plot_tree(tree, parent_pt, node_txt):
    """
    绘制出树的所有节点，递归绘制
    :param tree: 决策树
    :param parent_pt: 父节点的坐标
    :param node_txt: 节点的文本信息
    """
    num_leafs = get_num_leafs(tree)
    depth = get_tree_depth(tree)
    first_str = next(iter(tree))
    cntr_pt = (plot_tree.x_off + (1.0 + float(num_leafs)) / 2.0 / plot_tree.total_w, plot_tree.y_off)

    plot_mid_text(cntr_pt, parent_pt, node_txt)
    plot_node(first_str, cntr_pt, parent_pt, decisionNode)

    second_dict = tree[first_str]
    plot_tree.y_off = plot_tree.y_off - 1.0 / plot_tree.total_d

    for key in second_dict:
        if isinstance(second_dict[key], dict):
            plot_tree(second_dict[key], cntr_pt, str(key))
        else:
            plot_tree.x_off = plot_tree.x_off + 1.0 / plot_tree.total_w
            plot_node(second_dict[key], (plot_tree.x_off, plot_tree.y_off), cntr_pt, leafNode)
            plot_mid_text((plot_tree.x_off, plot_tree.y_off), cntr_pt, str(key))

    plot_tree.y_off = plot_tree.y_off + 1.0 / plot_tree.total_d

def create_plot(tree):
    """
    需要绘制的决策树
    :param tree: 决策树字典
    """
    fig = plt.figure(1, facecolor='white')
    fig.clf()
    axprops = dict(xticks=[], yticks=[])
    create_plot.ax1 = plt.subplot(111, frameon=False, **axprops)

    plot_tree.total_w = float(get_num_leafs(tree))
    plot_tree.total_d = float(get_tree_depth(tree))
    plot_tree.x_off = -0.5 / plot_tree.total_w
    plot_tree.y_off = 1.0

    plot_tree(tree, (0.5, 1.0), '')
    plt.show()

if __name__ == '__main__':
    test_tree = {'no surfacing': {0: 'no', 1: {'flippers': {0: 'no', 1: 'yes'}}, 3: 'maybe'}}
    create_plot(test_tree)
