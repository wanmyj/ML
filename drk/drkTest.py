from pydrake.common import FindResourceOrThrow
from pydrake.multibody.rigid_body_plant import RigidBodyPlant
from pydrake.multibody.rigid_body_tree import RigidBodyTree
from pydrake.systems.analysis import Simulator

tree = RigidBodyTree(
    FindResourceOrThrow("drake/examples/pendulum/Pendulum.urdf"))
simulator = Simulator(RigidBodyPlant(tree))