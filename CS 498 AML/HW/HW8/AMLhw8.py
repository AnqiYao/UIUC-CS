from PIL import Image
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
import matplotlib.image as img
import numpy as np
import time


im01 = img.imread('/RobertMixed03.jpg')
im02 = img.imread('/smallstrelitzia.jpg')
im03 = img.imread('/smallsunset.jpg')
im04 = img.imread('/Tree.jpg')
pixels01 = np.reshape(im01,  (im01.shape[0]*im01.shape[1], 3))
pixels02 = np.reshape(im02,  (im02.shape[0]*im03.shape[1], 3))
pixels03 = np.reshape(im03,  (im03.shape[0]*im03.shape[1], 3))
pixels04 = np.reshape(im04,  (im04.shape[0]*im04.shape[1], 3))


def initialize_parameters(pixels, num_seg):

    kmeans = KMeans(n_clusters = num_seg, init = "random", random_state = 0).fit(pixels)
    mu = kmeans.cluster_centers_
    pi = np.ones((num_seg, 1))/num_seg

    return mu, pi

def estimation(pixels, mu, pi):

    w = np.zeros((pixels.shape[0], mu.shape[0]))
    for x in range(pixels.shape[0]):
        pixel = np.array([pixels[x]]*mu.shape[0])
        diff = np.subtract(pixel, mu)
        square = np.multiply(diff, diff)
        min_idx = np.argmin(np.sum(square, axis = 1))
        dmin = square[min_idx]
        square = np.subtract(square, dmin)
        power = -1/2 * np.sum(square, axis=1)
        weight = np.multiply(np.exp(power), pi.T)
        w[x] = np.divide(weight, np.sum(weight))

    return w

def maximization(pixels, w):

    mu = np.zeros((w.shape[1], pixels.shape[1]))
    pi = np.zeros((w.shape[1], 1))
    for c in range(w.shape[1]):

        w_c = w.T[c]
        mu_num = np.matmul(pixels.T, w_c)
        mu_denom = np.sum(w_c)
        mu[c] = np.divide(mu_num, mu_denom)
        pi[c] = np.divide(mu_denom, pixels.shape[0])

    return mu, pi

def EM(iteration, pixels, mu, pi):
    for i in range(iteration):
        w = estimation(pixels, mu, pi)
        mu, pi = maximization(pixels, w)
    return mu, pi

def implot(im, mu):

    rows = im.shape[0]
    cols = im.shape[1]
    im_out = np.zeros((rows, cols, 3))
    for r in range(rows):
        for c in range(cols):
            idx = np.argmin(np.sum(np.abs(np.subtract(im[r,c,:], mu)), axis = 1))
            im_out[r,c,:] = mu[idx]

    return im_out

iteration = 10 # number of iterations
num_seg = 50 # number of segments

mu0, pi0 = initialize_parameters(pixels01, num_seg)
mu1, pi1 = EM(iteration, pixels01, mu0, pi0)
im01_out = implot(im01, mu1)
plt.figure()
plt.imshow(im01_out/255)
plt.imsave("im01_cluster50.png", im01_out/255)

mu0, pi0 = initialize_parameters(pixels02, num_seg)
mu2, pi2 = EM(iteration, pixels02, mu0, pi0)
im02_out = implot(im02, mu2)
plt.figure()
plt.imshow(im02_out/255)
plt.imsave("im02_cluster50.png", im02_out/255)

mu0, pi0 = initialize_parameters(pixels03, num_seg)
mu3, pi3 = EM(iteration, pixels03, mu0, pi0)
im03_out = implot(im03, mu3)
plt.figure()
plt.imshow(im03_out/255)
plt.imsave("im03_cluster50.png", im03_out/255)

mu0, pi0 = initialize_parameters(pixels04, num_seg)
mu4, pi4 = EM(iteration, pixels04, mu0, pi0)
im04_out = implot(im04, mu4)
plt.figure()
plt.imshow(im04_out/255)
plt.imsave("im04_cluster50.png", im04_out/255)

# five different starting_points
starting_points=[]
for i in range(5):
    kmeans = KMeans(n_clusters = 20, init = "random").fit(pixels04)
    mu = kmeans.cluster_centers_
    starting_points.append(mu)

num_seg = 20
iteration = 10
pi0 = np.ones((num_seg, 1))/num_seg
for i in range(5):
    mu, pi = EM(iteration, pixels04, starting_points[i], pi0)
    im04_out = implot(im04, mu)
    plt.figure()
    plt.imshow(im04_out/255)
    plt.imsave("im04_cluster20_{}.png".format(i), im04_out/255)
