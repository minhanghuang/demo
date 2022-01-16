# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: geometry.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='geometry.proto',
  package='trunk.msgs',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x0egeometry.proto\x12\ntrunk.msgs\x1a\x1fgoogle/protobuf/timestamp.proto\"V\n\x06Header\x12\x0b\n\x03seq\x18\x01 \x01(\r\x12-\n\ttimestamp\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x10\n\x08\x66rame_id\x18\x03 \x01(\t\"\x1f\n\x07Point2D\x12\t\n\x01x\x18\x01 \x01(\x01\x12\t\n\x01y\x18\x02 \x01(\x01\"*\n\x07Point3D\x12\t\n\x01x\x18\x01 \x01(\x01\x12\t\n\x01y\x18\x02 \x01(\x01\x12\t\n\x01z\x18\x03 \x01(\x01\"9\n\x07Point4D\x12\t\n\x01x\x18\x01 \x01(\x01\x12\t\n\x01y\x18\x02 \x01(\x01\x12\t\n\x01z\x18\x03 \x01(\x01\x12\r\n\x05theta\x18\x04 \x01(\x01\"<\n\nQuaternion\x12\n\n\x02qx\x18\x01 \x01(\x01\x12\n\n\x02qy\x18\x02 \x01(\x01\x12\n\n\x02qz\x18\x03 \x01(\x01\x12\n\n\x02qw\x18\x04 \x01(\x01\"*\n\x07Vector3\x12\t\n\x01x\x18\x01 \x01(\x01\x12\t\n\x01y\x18\x02 \x01(\x01\x12\t\n\x01z\x18\x03 \x01(\x01\"Z\n\x04Pose\x12%\n\x08position\x18\x01 \x01(\x0b\x32\x13.trunk.msgs.Point3D\x12+\n\x0borientation\x18\x02 \x01(\x0b\x32\x16.trunk.msgs.Quaternion\"\\\n\x0bPoseStamped\x12-\n\ttimestamp\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x1e\n\x04pose\x18\x02 \x01(\x0b\x32\x10.trunk.msgs.Pose\"R\n\x05Twist\x12#\n\x06linear\x18\x01 \x01(\x0b\x32\x13.trunk.msgs.Vector3\x12$\n\x07\x61ngular\x18\x02 \x01(\x0b\x32\x13.trunk.msgs.Vector3\"3\n\x03RPY\x12\x0c\n\x04roll\x18\x01 \x01(\x01\x12\r\n\x05pitch\x18\x02 \x01(\x01\x12\x0f\n\x07heading\x18\x03 \x01(\x01\"\xc9\x01\n\tTransform\x12\x10\n\x08\x66rame_id\x18\x01 \x01(\t\x12\x10\n\x08\x63hild_id\x18\x02 \x01(\t\x12(\n\x0btranslation\x18\x03 \x01(\x0b\x32\x13.trunk.msgs.Vector3\x12(\n\x08rotation\x18\x04 \x01(\x0b\x32\x16.trunk.msgs.Quaternion\x12&\n\tdelta_pos\x18\x05 \x01(\x0b\x32\x13.trunk.msgs.Vector3\x12\x1c\n\x03rpy\x18\x06 \x01(\x0b\x32\x0f.trunk.msgs.RPYb\x06proto3')
  ,
  dependencies=[google_dot_protobuf_dot_timestamp__pb2.DESCRIPTOR,])




_HEADER = _descriptor.Descriptor(
  name='Header',
  full_name='trunk.msgs.Header',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='seq', full_name='trunk.msgs.Header.seq', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='trunk.msgs.Header.timestamp', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='frame_id', full_name='trunk.msgs.Header.frame_id', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=63,
  serialized_end=149,
)


_POINT2D = _descriptor.Descriptor(
  name='Point2D',
  full_name='trunk.msgs.Point2D',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='trunk.msgs.Point2D.x', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='y', full_name='trunk.msgs.Point2D.y', index=1,
      number=2, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=151,
  serialized_end=182,
)


_POINT3D = _descriptor.Descriptor(
  name='Point3D',
  full_name='trunk.msgs.Point3D',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='trunk.msgs.Point3D.x', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='y', full_name='trunk.msgs.Point3D.y', index=1,
      number=2, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='z', full_name='trunk.msgs.Point3D.z', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=184,
  serialized_end=226,
)


_POINT4D = _descriptor.Descriptor(
  name='Point4D',
  full_name='trunk.msgs.Point4D',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='trunk.msgs.Point4D.x', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='y', full_name='trunk.msgs.Point4D.y', index=1,
      number=2, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='z', full_name='trunk.msgs.Point4D.z', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='theta', full_name='trunk.msgs.Point4D.theta', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=228,
  serialized_end=285,
)


_QUATERNION = _descriptor.Descriptor(
  name='Quaternion',
  full_name='trunk.msgs.Quaternion',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='qx', full_name='trunk.msgs.Quaternion.qx', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='qy', full_name='trunk.msgs.Quaternion.qy', index=1,
      number=2, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='qz', full_name='trunk.msgs.Quaternion.qz', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='qw', full_name='trunk.msgs.Quaternion.qw', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=287,
  serialized_end=347,
)


_VECTOR3 = _descriptor.Descriptor(
  name='Vector3',
  full_name='trunk.msgs.Vector3',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='trunk.msgs.Vector3.x', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='y', full_name='trunk.msgs.Vector3.y', index=1,
      number=2, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='z', full_name='trunk.msgs.Vector3.z', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=349,
  serialized_end=391,
)


_POSE = _descriptor.Descriptor(
  name='Pose',
  full_name='trunk.msgs.Pose',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='position', full_name='trunk.msgs.Pose.position', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='orientation', full_name='trunk.msgs.Pose.orientation', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=393,
  serialized_end=483,
)


_POSESTAMPED = _descriptor.Descriptor(
  name='PoseStamped',
  full_name='trunk.msgs.PoseStamped',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='trunk.msgs.PoseStamped.timestamp', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pose', full_name='trunk.msgs.PoseStamped.pose', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=485,
  serialized_end=577,
)


_TWIST = _descriptor.Descriptor(
  name='Twist',
  full_name='trunk.msgs.Twist',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='linear', full_name='trunk.msgs.Twist.linear', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='angular', full_name='trunk.msgs.Twist.angular', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=579,
  serialized_end=661,
)


_RPY = _descriptor.Descriptor(
  name='RPY',
  full_name='trunk.msgs.RPY',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='roll', full_name='trunk.msgs.RPY.roll', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pitch', full_name='trunk.msgs.RPY.pitch', index=1,
      number=2, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='heading', full_name='trunk.msgs.RPY.heading', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=663,
  serialized_end=714,
)


_TRANSFORM = _descriptor.Descriptor(
  name='Transform',
  full_name='trunk.msgs.Transform',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='frame_id', full_name='trunk.msgs.Transform.frame_id', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='child_id', full_name='trunk.msgs.Transform.child_id', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='translation', full_name='trunk.msgs.Transform.translation', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='rotation', full_name='trunk.msgs.Transform.rotation', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='delta_pos', full_name='trunk.msgs.Transform.delta_pos', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='rpy', full_name='trunk.msgs.Transform.rpy', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=717,
  serialized_end=918,
)

_HEADER.fields_by_name['timestamp'].message_type = google_dot_protobuf_dot_timestamp__pb2._TIMESTAMP
_POSE.fields_by_name['position'].message_type = _POINT3D
_POSE.fields_by_name['orientation'].message_type = _QUATERNION
_POSESTAMPED.fields_by_name['timestamp'].message_type = google_dot_protobuf_dot_timestamp__pb2._TIMESTAMP
_POSESTAMPED.fields_by_name['pose'].message_type = _POSE
_TWIST.fields_by_name['linear'].message_type = _VECTOR3
_TWIST.fields_by_name['angular'].message_type = _VECTOR3
_TRANSFORM.fields_by_name['translation'].message_type = _VECTOR3
_TRANSFORM.fields_by_name['rotation'].message_type = _QUATERNION
_TRANSFORM.fields_by_name['delta_pos'].message_type = _VECTOR3
_TRANSFORM.fields_by_name['rpy'].message_type = _RPY
DESCRIPTOR.message_types_by_name['Header'] = _HEADER
DESCRIPTOR.message_types_by_name['Point2D'] = _POINT2D
DESCRIPTOR.message_types_by_name['Point3D'] = _POINT3D
DESCRIPTOR.message_types_by_name['Point4D'] = _POINT4D
DESCRIPTOR.message_types_by_name['Quaternion'] = _QUATERNION
DESCRIPTOR.message_types_by_name['Vector3'] = _VECTOR3
DESCRIPTOR.message_types_by_name['Pose'] = _POSE
DESCRIPTOR.message_types_by_name['PoseStamped'] = _POSESTAMPED
DESCRIPTOR.message_types_by_name['Twist'] = _TWIST
DESCRIPTOR.message_types_by_name['RPY'] = _RPY
DESCRIPTOR.message_types_by_name['Transform'] = _TRANSFORM
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Header = _reflection.GeneratedProtocolMessageType('Header', (_message.Message,), {
  'DESCRIPTOR' : _HEADER,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.Header)
  })
_sym_db.RegisterMessage(Header)

Point2D = _reflection.GeneratedProtocolMessageType('Point2D', (_message.Message,), {
  'DESCRIPTOR' : _POINT2D,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.Point2D)
  })
_sym_db.RegisterMessage(Point2D)

Point3D = _reflection.GeneratedProtocolMessageType('Point3D', (_message.Message,), {
  'DESCRIPTOR' : _POINT3D,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.Point3D)
  })
_sym_db.RegisterMessage(Point3D)

Point4D = _reflection.GeneratedProtocolMessageType('Point4D', (_message.Message,), {
  'DESCRIPTOR' : _POINT4D,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.Point4D)
  })
_sym_db.RegisterMessage(Point4D)

Quaternion = _reflection.GeneratedProtocolMessageType('Quaternion', (_message.Message,), {
  'DESCRIPTOR' : _QUATERNION,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.Quaternion)
  })
_sym_db.RegisterMessage(Quaternion)

Vector3 = _reflection.GeneratedProtocolMessageType('Vector3', (_message.Message,), {
  'DESCRIPTOR' : _VECTOR3,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.Vector3)
  })
_sym_db.RegisterMessage(Vector3)

Pose = _reflection.GeneratedProtocolMessageType('Pose', (_message.Message,), {
  'DESCRIPTOR' : _POSE,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.Pose)
  })
_sym_db.RegisterMessage(Pose)

PoseStamped = _reflection.GeneratedProtocolMessageType('PoseStamped', (_message.Message,), {
  'DESCRIPTOR' : _POSESTAMPED,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.PoseStamped)
  })
_sym_db.RegisterMessage(PoseStamped)

Twist = _reflection.GeneratedProtocolMessageType('Twist', (_message.Message,), {
  'DESCRIPTOR' : _TWIST,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.Twist)
  })
_sym_db.RegisterMessage(Twist)

RPY = _reflection.GeneratedProtocolMessageType('RPY', (_message.Message,), {
  'DESCRIPTOR' : _RPY,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.RPY)
  })
_sym_db.RegisterMessage(RPY)

Transform = _reflection.GeneratedProtocolMessageType('Transform', (_message.Message,), {
  'DESCRIPTOR' : _TRANSFORM,
  '__module__' : 'geometry_pb2'
  # @@protoc_insertion_point(class_scope:trunk.msgs.Transform)
  })
_sym_db.RegisterMessage(Transform)


# @@protoc_insertion_point(module_scope)