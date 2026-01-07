from matplotlib import pyplot as plt

n = int(input())

xs = []
ys = []
for i in range(n):
    x, y = map(int, input().split(' '))
    xs.append(x)
    ys.append(y)
print(xs)
print(ys)

label = input()
while True:
    if label != "frame":
        break
    fig, ax = plt.subplots()
    ax.set_aspect('equal')
    ax.scatter(xs, ys)
    print("frame")

    while True:
        text = input()
        if text[0] == '-':
            _, p1, p2 = text.split(' ')
            p1 = int(p1)
            p2 = int(p2)
            print("remove", p1, p2)
            ax.plot([xs[p1], xs[p2]], [ys[p1], ys[p2]], color='blue')
            ax.scatter([xs[p1], xs[p2]], [ys[p1], ys[p2]], color='red')
        elif text[0] == '+':
            _, p1, p2 = text.split(' ')
            p1 = int(p1)
            p2 = int(p2)
            print("add", p1, p2)
            ax.plot([xs[p1], xs[p2]], [ys[p1], ys[p2]], color='red')
            ax.scatter([xs[p1], xs[p2]], [ys[p1], ys[p2]], color='red')
        else:
            label = text
            break

    plt.show()

